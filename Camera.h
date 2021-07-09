#pragma once
class Camera {
public:
	int x;
	int y;
	int w;
	int h;
	SDL_Rect* Cam;

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

	bool PutX(int xPos) {
		x = xPos;
		Cam->x = xPos;
		return true;
	}

	bool PutY(int yPos) {
		y = yPos;
		Cam->y = yPos;
		return true;
	}


	bool MoveX(int xVec) {
		x += xVec;
		// will have to make more tests for this check
		if (x < 0 || x + (SCREEN_WIDTH * TILE_WIDTH) > LEVEL_WIDTH * TILE_WIDTH) { // this keeps the camera from going out of the level
			x -= xVec;
			return false;
		}
		else {
			Cam->x = x;
			return true;
		}
	}

	bool MoveY(int yVec) {
		y += yVec;
		// will have to make more tests for this check
		if (y < 0 || y + (SCREEN_HEIGHT * TILE_HEIGHT) > LEVEL_HEIGHT * TILE_HEIGHT) { // this keeps the camera from going out of the level
			y -= yVec;
			return false;
		}
		else {
			Cam->y = y;
			return true;
		}
	}

	int GetXPos() {
		return x;
	}

	int GetYPos() {
		return y;
	}
};