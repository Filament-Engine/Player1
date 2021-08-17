#pragma once

// this is the player class -- what the user controls
class Player : public Sprite {
public:
	SDL_Rect* SelfTile;
	SDL_Texture* SelfImg;
	SDL_Surface* TempOrigin;

	Player(int DefaultSpawnX, int DefaultSpawnY, int DefaultPixelH, int DefaultPixelW, std::string SourceKey, int SourceCoordx, int SourceCoordy, int SourcePixelH, int SourcePixelW, int xVelocity, int yVelocity, std::map<std::string, SurfaceProperty*> SurfacePropertyMap) {

		xPos = DefaultSpawnX;
		yPos = DefaultSpawnY;

		IMGName = SourceKey; //AA

		SourceTile = new SDL_Rect();
		SelfTile = new SDL_Rect();
		TargetTile = new SDL_Rect();
		SourceTile->x = SourceCoordx * TILE_WIDTH;
		SourceTile->y = SourceCoordy * TILE_HEIGHT;
		SourceTile->h = SourcePixelH;
		SourceTile->w = SourcePixelW;

		SelfTile->x = 0;
		SelfTile->y = 0;
		SelfTile->h = SourcePixelH;
		SelfTile->w = SourcePixelW;
		//grab a portion of a texture, and make a texture.

		TargetTile->x = DefaultSpawnX;
		TargetTile->y = DefaultSpawnY;
		TargetTile->w = DefaultPixelH;
		TargetTile->h = DefaultPixelW;
		//Surface -> Texture
		TempOrigin = SDL_CreateRGBSurface(0, SourceTile->w, SourceTile->h, 32, 0, 0, 0, 0);

		SDL_BlitSurface(SurfacePropertyMap[IMGName]->GetSelfSurface(), SourceTile, TempOrigin, SelfTile);

		//case Temp Origin to a texture
		SelfImg = SDL_CreateTextureFromSurface(gRenderer, TempOrigin);
		xVec = xVelocity;
		yVec = yVelocity;


	}
	~Player() {
		printf("Destruct Player\n");
	}
	// moves the player, moved the camera, detects for collision, detects for level barriers, all along the y-axis. returns 1 if the player icon moves, 0 if not.
	bool MoveY(int yVelocity, int**& CombinedCollision) { //moves the palyer in the y direction
		yPos += yVelocity;

		if (yVelocity < 0) { // if moving up -- detecting collision
			if (1 == CombinedCollision[yPos / TILE_HEIGHT][xPos / TILE_WIDTH] || 1 == CombinedCollision[(yPos / TILE_HEIGHT)][(xPos + GetWidth() - 1) / TILE_WIDTH]) {
				yPos -= yVelocity;
				return 0;
			}
		}

		else if (yVelocity > 0 && yPos < LEVEL_HEIGHT * TILE_HEIGHT - GetHeight()) { // if moving down -- detecting collision -- the second statement is so that it doesn't go through here when its at the edge
			if (1 == CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][xPos / TILE_WIDTH] || 1 == CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][(xPos + GetWidth() - 1) / TILE_WIDTH]) { // check for right collision
				yPos -= yVelocity; // reverts the movement change
				return 0; // fails it
			}
		}

		if (yPos < (LEVEL_HEIGHT * TILE_HEIGHT) - (SCREEN_HEIGHT * TILE_HEIGHT / 2) && yPos >(SCREEN_HEIGHT * TILE_HEIGHT / 2)) { // this will move camera
			gCamera->MoveY(yVelocity); // this moves the camera by the yVelocity value
			return 0;
		}
		else if (yPos < (SCREEN_HEIGHT * TILE_HEIGHT / 2) && gCamera->y > 0) { // NEW
			gCamera->MoveY(yVelocity); // the only situation in which this action takes place is when the camera is moving up; thus yVelocity must be negative, so we are subtracting the camera by adding yVelocity
			return 0;
		}
		else if (yPos > (LEVEL_HEIGHT * TILE_HEIGHT) - (SCREEN_HEIGHT * TILE_HEIGHT / 2) && gCamera->y < LEVEL_HEIGHT * TILE_HEIGHT - SCREEN_HEIGHT * TILE_HEIGHT - 1) { // NEW -- this is for some reason unncessary on x-axis but not y
			gCamera->MoveY(yVelocity); // the only time when this action happens is when we are moving doown, thus yVelocity would be positive.
			return 0;
		}
		else { // this will move the player icon
			if (yPos < 0 || yPos + GetHeight() - 1 >= LEVEL_HEIGHT * TILE_HEIGHT) { // determines if it is in bounds -- if it is not, go through this if statement
				yPos -= yVelocity;
				return 0;
			}
			else {
				// TargetTile->y += yVelocity; // actually moves the player
				return 1;
			}
		}
	}
	// moves the player, moved the camera, detects for collision, detects for level barriers, all along the x-axis. returns 1 if the player icon moves, 0 if not.
	bool MoveX(int xVelocity, int**& CombinedCollision) { //moves the player in the x direction
		xPos += xVelocity;
		if (xVelocity < 0) { // if moving left
			if (1 == CombinedCollision[yPos / TILE_HEIGHT][(xPos / TILE_WIDTH)] || 1 == CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][(xPos / TILE_WIDTH)]) { // check for left collision
				xPos -= xVelocity; // reverts the movement change
				return 0; // fails it
			}
		}
		else if (xVelocity > 0 && xPos < LEVEL_WIDTH * TILE_WIDTH - GetWidth()) { // if moving right -- the second statemenet means it won't go through if it's at the edge
			if (1 == CombinedCollision[yPos / TILE_HEIGHT][(xPos + GetWidth() - 1) / TILE_WIDTH] || 1 == CombinedCollision[(yPos + GetHeight() - 1) / TILE_HEIGHT][(xPos + GetWidth() - 1) / TILE_WIDTH]) { // check for right collision
				xPos -= xVelocity; // reverts the movement change
				return 0; // fails it
			}
		}
		if (xPos < (LEVEL_WIDTH * TILE_WIDTH) - (SCREEN_WIDTH * TILE_WIDTH / 2) && xPos >(SCREEN_WIDTH * TILE_WIDTH / 2)) { // this will move camera
			gCamera->MoveX(xVelocity);
			return 0; // the player icon did not move (only the camera)
		}
		else if (xPos < (SCREEN_WIDTH * TILE_WIDTH / 2) && gCamera->x > 0) {
			gCamera->MoveX(xVelocity);  // this will only happen when we're moving left, thus, xVelocity would be negative. therefore, we are subtracting through addition.
			return 0;
		}
		else if (xPos > (LEVEL_WIDTH * TILE_WIDTH) - (SCREEN_WIDTH * TILE_WIDTH / 2) && gCamera->x < LEVEL_WIDTH * TILE_WIDTH - SCREEN_WIDTH * TILE_WIDTH - 1) {
			gCamera->MoveX(xVelocity); // this will only happen when we're moving right, thus, xVelocity would be positive. thus, we are just adding as normal.
			return 0;
		}

		else { // this will move the player icon
			if (xPos < 0 || xPos + GetWidth() - 1 >= LEVEL_WIDTH * TILE_WIDTH) { // checks to see if position is out of bounds
				xPos -= xVelocity;
				return 0;
			}
			else { // if not out of bounds, move
				return 1; // the player icon moved
			}
		}
	}
	int getXPos() { // returns the x position
		return xPos;
	}
	int getYPos() { // returns the y position
		return yPos;
	}
	//make a second to handle new target positions, in the event it is changed idk.
	void RenderThis() {
		//Test Blitting is very bad, so what actually happens is it automatically wipes the information of the previous surface. So lets try placing a texture over it, and just grabe the texture from the target texture.
		SDL_RenderCopy(gRenderer, SelfImg, NULL, TargetTile);
	};
	int GetWidth() {
		return SelfTile->w;
	}
	int GetHeight() {
		return SelfTile->h;
	}
};
