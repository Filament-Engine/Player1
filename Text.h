#pragma once

class Text {
public:
	SDL_Texture* textTexture;
	SDL_Rect* text_rect;
	TTF_Font* Font;
	SDL_Color TextColor;
	std::string Message;
	bool StayInPlace;

	// this is our constructor for the text
	Text(const char* font_path, std::string message, int font_size, SDL_Color Color, int xPos, int yPos, bool Stay) { // this is the constructor for placing it on a level instead of camera position
		Font = TTF_OpenFont(font_path, font_size);
		TextColor = Color;
		Message = message;
		StayInPlace = Stay; // this determines if the text follows the player or stays in place

		if (Font == NULL)
		{
			printf("Failed to load font: %s\n", TTF_GetError());
		}
		else
		{
			text_rect = new SDL_Rect;
			text_rect->x = xPos;
			text_rect->y = yPos;

			// here we create the text surface
			SDL_Surface* textSurface = TTF_RenderText_Blended(Font, Message.c_str(), TextColor);

			if (StayInPlace) {

				SDL_Surface* levelSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
				
				SDL_BlitSurface(textSurface, NULL, levelSurface, text_rect); // blits the text onto our level surface
				
				textTexture = SDL_CreateTextureFromSurface(gRenderer, levelSurface); // converts the surface to a texture

				SDL_FreeSurface(levelSurface); // releasing the surface
			}
			else {
				textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface); // converts the surface to a texture
			}

			SDL_FreeSurface(textSurface); // releasing the surface
			SDL_QueryTexture(textTexture, 0, 0, &text_rect->w, &text_rect->h);
		}
	}

	// this changes the message
	void UpdateMessage(std::string new_message) {
		Message = new_message;

		SDL_Surface* textSurface = TTF_RenderText_Blended(Font, Message.c_str(), TextColor);

		if (StayInPlace) {
			SDL_Surface* levelSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

			SDL_BlitSurface(textSurface, NULL, levelSurface, text_rect);

			textTexture = SDL_CreateTextureFromSurface(gRenderer, levelSurface);

			SDL_FreeSurface(levelSurface);
		}
		else {
			textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		}
		
		SDL_FreeSurface(textSurface);
		SDL_QueryTexture(textTexture, 0, 0, &text_rect->w, &text_rect->h);
	}

	// this function changes the color of the text
	void ChangeColor(SDL_Color color) {
		TextColor = color;

		SDL_Surface* textSurface = TTF_RenderText_Blended(Font, Message.c_str(), TextColor);
		if (StayInPlace) {
			SDL_Surface* levelSurface = SDL_CreateRGBSurface(0, LEVEL_WIDTH * TILE_WIDTH, LEVEL_HEIGHT * TILE_HEIGHT, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

			SDL_BlitSurface(textSurface, NULL, levelSurface, text_rect);

			textTexture = SDL_CreateTextureFromSurface(gRenderer, levelSurface);

			SDL_FreeSurface(levelSurface);
		}
		else {
			textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		}

		SDL_FreeSurface(textSurface);
	}


	void MoveX(int x) {
		text_rect->x += x;
	}

	void MoveY(int y) {
		text_rect->y += y;
	}

	void TeleportX(int x) {
		text_rect->x = x;
	}

	void TeleportY(int y) {
		text_rect->y = y;
	}

	// this display takes the default x and y position and displays it there
	void Display() {
		if (StayInPlace) {
			SDL_RenderCopy(gRenderer, textTexture, gCamera->Cam, gFullWindowRect);
		}
		else {
			SDL_RenderCopy(gRenderer, textTexture, NULL, text_rect);
		}
	}
	// this display lets us choose where we want it displayed
	void Display(int x, int y) {
		text_rect->x = x;
		text_rect->y = y;
		if (StayInPlace) {
			SDL_RenderCopy(gRenderer, textTexture, gCamera->Cam, gFullWindowRect);
		}
		else {
			SDL_RenderCopy(gRenderer, textTexture, NULL, text_rect);
		}
	}
};