#pragma once
class Camera {
public:
	int x; // the x position of the camera
	int y; // the y position of the camera
	int w; // the width of the camera: TILE_WIDTH * SCREEN_WIDTH
	int h; // the height of the camera: TILE_HEIGHT * SCREEN_HEIGHT
	SDL_Rect* Cam; // the rectangle we will use for 

	Camera(int xPos, int yPos) {
		x = xPos;
		y = yPos;
		w = SCREEN_WIDTH * TILE_WIDTH;
		h = SCREEN_HEIGHT * TILE_HEIGHT; 

		
		Cam = new SDL_Rect;
		Cam->x = x;
		Cam->y = y;
		Cam->w = w;
		Cam->h = h;
	}

	bool TeleportX(int xPos) { // put some new value into the x position -- teleports
		x = xPos;
		Cam->x = xPos;
		return true;
	}

	bool TeleportY(int yPos) { // put some new value into the y position -- teleports
		y = yPos;
		Cam->y = yPos;
		return true;
	}


	bool MoveX(int xVec) { // moves the x position of the camera by the xVec
		x += xVec;
		if (x < 0 || x + (SCREEN_WIDTH * TILE_WIDTH) > LEVEL_WIDTH * TILE_WIDTH) { // this keeps the camera from going out of the level
			x -= xVec;
			return false;
		}
		else { // if the movement does not put the camera out of bounds, move it
			Cam->x = x;
			return true;
		}
	}

	bool MoveY(int yVec) { // moves the y position of the camera by the yVec
		y += yVec;
		if (y < 0 || y + (SCREEN_HEIGHT * TILE_HEIGHT) > LEVEL_HEIGHT * TILE_HEIGHT) { // this keeps the camera from going out of the level
			y -= yVec;
			return false;
		}
		else { // if the movement does not put the camera out of bounds, move it 
			Cam->y = y;
			return true;
		}
	}

	int GetXPos() { // returns the x position
		return x;
	}

	int GetYPos() { // returns the y position
		return y;
	}
};