#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include "Object.h"
#include "Player.h"
#include "Text.h"
#include "Button.h"


class Window
{
	public:
		std::vector<Object> objects;
		std::vector<Object>::size_type index;
		int objectSpeed;

		Window(std::string windowName, int windowWidth, int windowHeight);
		void clear(Uint8 r, Uint8 g, Uint8 b);
		void update();
		void renderRect(SDL_Rect rect, SDL_Color color);
		void renderRect(Object obj);
		void renderText(Text text);
		void renderButton(Button button);
		void destroy();
		void addObject(int x, int y, int w, int h);
		void loadObjectsFromFile(std::string filePath);
		void loadObjectsFromFile(std::string filePath, int offset); // DELETE
		void loadRandomScene();
		bool updateObjects(Player &player);
		void renderObjects();
		SDL_Renderer* getRenderer();
		SDL_Window* getWindow();

	private:
		SDL_Window *window = nullptr;
		SDL_Renderer *renderer = nullptr;
};