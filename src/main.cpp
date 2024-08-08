#include <SDL.h>
#include <SDL_ttf.h>
#include "Window.h"
#include "Player.h"
#include "Object.h"
#include "Text.h"
#include "Button.h"
#include "KeyboardHandler.h"
#include "constants.h"


int main(int argc, char* argv[])
{
	// SDL SETUP
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	// WINDOW
	Window window("Game", constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT);

	// TITLE
	Text title(constants::FONT_PATH, 50, 255, 255, 255, "*Working Title", 20, 100, window.getRenderer());
	title.center();

	// PLAY BUTTON
	Button play(constants::FONT_PATH, 24, 255, 255, 255, "NORMAL", 20, 250, window.getRenderer(), true);
	play.updateBackground(100, 50, 0, 0, 0);
	
	// DOUBLE TIME BUTTON
	Button doubleTime(constants::FONT_PATH, 24, 255, 255, 255, "DOUBLE TIME", 20, 300, window.getRenderer(), true);
	doubleTime.updateBackground(150, 50, 0, 0, 0);

	// EXIT BUTTON
	Button exit(constants::FONT_PATH, 24, 255, 255, 255, "EXIT", 20, 400, window.getRenderer(), true);
	exit.updateBackground(60, 30, 0, 0, 0);

	// OTHER VARS
	KeyboardHandler keyboardHandler;
	SDL_Event windowEvent;
	bool titleScreenRunning = true;
	bool gameRunning = false;
	while (titleScreenRunning)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			switch (windowEvent.type)
			{
				// BUTTONS CLICKED
				case SDL_MOUSEBUTTONUP:
					if (play.isClicked(windowEvent))
					{
						titleScreenRunning = false;
						gameRunning = true;
					}
					else if (doubleTime.isClicked(windowEvent))
					{
						titleScreenRunning = false;
						gameRunning = true;
						window.objectSpeed = 2;
					}
					else if (exit.isClicked(windowEvent))
						titleScreenRunning = false;
					break;

				// BUTTON HOVER
				case SDL_MOUSEMOTION:
					play.changeColorWhenHover(windowEvent, 255, 255, 255, 0, 0, 0, window.getRenderer());
					doubleTime.changeColorWhenHover(windowEvent, 255, 255, 255, 0, 0, 0, window.getRenderer());
					exit.changeColorWhenHover(windowEvent, 255, 255, 255, 0, 0, 0, window.getRenderer());
					break;
				
				default:
					break;
			}
		}
		if (titleScreenRunning == false || keyboardHandler.keyPressed(SDL_SCANCODE_ESCAPE))
			break;

		// CLEAR SCREEN
		window.clear(0, 0, 0);
		
		// RENDER
		window.renderText(title);
		window.renderButton(play);
		window.renderButton(doubleTime);
		window.renderButton(exit);
		
		// UPDATE WINDOW
		window.update();
	}

	// CLEAN UP TITLE AND BUTTONS
	title.destroy();
	play.destroy();
	doubleTime.destroy();
	exit.destroy();

	// PLAYER
	Player player(0, constants::WINDOW_HEIGHT-20, 20, 20, 255, 255, 255);
	
	// OBJECTS
	window.loadRandomScene();
	//window.loadObjectsFromFile("dscene2.txt", 500);

	// TEXT
	double score = 0;
	Text scoreText(constants::FONT_PATH, 24, 255, 255, 255, std::to_string((int) score), 20, 20, window.getRenderer());
	scoreText.center();
	Text game_over(constants::FONT_PATH, 24, 255, 255, 255, "GAME OVER", 20, 100, window.getRenderer());
	game_over.center();

	while (gameRunning)
	{
		// QUIT
		if (SDL_PollEvent(&windowEvent))
		{
			switch (windowEvent.type)
			{
				case SDL_QUIT:
					gameRunning = false;
					break;
				
				default:
					break;
			}
		}
		if (gameRunning == false || keyboardHandler.keyPressed(SDL_SCANCODE_ESCAPE))
			break;
		
		// MOVEMENT
		if (keyboardHandler.keyPressed(SDL_SCANCODE_W))
			player.jump();
		if (keyboardHandler.keyPressed(SDL_SCANCODE_A))
			player.move(LEFT);
		if (keyboardHandler.keyPressed(SDL_SCANCODE_D))
			player.move(RIGHT);

		// UPDATE STUFF
		if (window.updateObjects(player))
		{
			// GAME OVER
			window.renderText(game_over);
			window.update();

			// WAIT FOR KEY PRESS
			while (!keyboardHandler.keyPressed())
			{
				SDL_PumpEvents();
			}
			break;
		}
		player.update(window.objects);

		// CLEAR SCREEN
		window.clear(0, 0, 0);
		
		// RENDER
		window.renderRect(player);

		window.renderObjects();

		window.renderText(scoreText);

		// UPDATE SCORE
		if (window.objectSpeed == 0)
			score += 0.05;
		else
			score += 0.1;
		scoreText.updateText(std::to_string((int) score), window.getRenderer());
		scoreText.center();

		// UPDATE WINDOW
		window.update();

		// FRAME RATE
		SDL_Delay(constants::FRAMES);
	}

	// CLEAN UP (NGL THIS WAS CLEEN FOR FOREVER)
	scoreText.destroy();
	game_over.destroy();
	window.destroy();

	TTF_Quit();
	SDL_Quit();

	return 0;
}