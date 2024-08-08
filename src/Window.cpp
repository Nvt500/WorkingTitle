#include "Window.h"


Window::Window(std::string windowName, int windowWidth, int windowHeight) : index(-1), objectSpeed(1)
{
	this->window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);

	if (this->window == NULL)
	{
		this->renderer = NULL;
		return;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	if (this->renderer == NULL)
	{
		this->window = NULL;
		return;
	}

	srand(time(NULL));
}


void Window::clear(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetRenderDrawColor(this->renderer, r, g, b, 255);
	SDL_RenderClear(this->renderer);
}


void Window::update()
{
	SDL_RenderPresent(this->renderer);
}


void Window::renderRect(SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(this->renderer, &rect);
}


void Window::renderRect(Object obj)
{
	SDL_SetRenderDrawColor(this->renderer, obj.color.r, obj.color.g, obj.color.b, obj.color.a);
	SDL_RenderFillRect(this->renderer, &obj.rect);
}


void Window::renderText(Text text)
{
	SDL_SetRenderDrawColor(this->renderer, text.color.r, text.color.g, text.color.b, text.color.a);
	SDL_RenderCopy(this->renderer, text.texture, NULL, &text.rect);
}


void Window::renderButton(Button button)
{
	SDL_SetRenderDrawColor(this->renderer, button.backgroundColor.r, button.backgroundColor.g, button.backgroundColor.b, button.backgroundColor.a);
	SDL_RenderFillRect(this->renderer, &button.background);
	SDL_SetRenderDrawColor(this->renderer, button.text.color.r, button.text.color.g, button.text.color.b, button.text.color.a);
	SDL_RenderCopy(this->renderer, button.text.texture, NULL, &button.text.rect);
}


void Window::destroy()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	this->renderer = NULL;
	this->window = NULL;
	this->objects.clear();
}


SDL_Renderer* Window::getRenderer()
{
	return this->renderer;
}


SDL_Window* Window::getWindow()
{
	return this->window;
}


void Window::addObject(int x, int y, int w, int h)
{
	this->objects.push_back(Object::Object(x, y, w, h, 255, 255, 255));
}


static int valueFromFile(std::ifstream &file)
{
	std::string line;
	while (true)
	{
		char c = file.get();
		if (c == ' ' || c == '\n' || c == EOF)
			break;
		line.push_back(c);
	}
	return std::stoi(line);
}


void Window::loadObjectsFromFile(std::string filePath)
{
	std::ifstream file(filePath);
	int offset = 0;

	int x = valueFromFile(file);
	if (this->index == -1)
		offset = constants::WINDOW_WIDTH - x;
	else
		offset = this->objects.at(this->index - 1).rect.x + this->objects.at(this->index - 1).rect.w - x + (constants::WINDOW_WIDTH / 2);
	int y = valueFromFile(file);
	int w = valueFromFile(file);
	int h = valueFromFile(file);

	this->addObject(x + offset, y, w, h);

	while (file)
	{
		x = valueFromFile(file);
		y = valueFromFile(file);
		w = valueFromFile(file);
		h = valueFromFile(file);

		this->addObject(x + offset, y, w, h);
	}

	if (this->index == -1)
		this->index = this->objects.size();
}


void Window::loadObjectsFromFile(std::string filePath, int offset)
{
	std::ifstream file(filePath);

	int x = valueFromFile(file);
	int y = valueFromFile(file);
	int w = valueFromFile(file);
	int h = valueFromFile(file);

	this->addObject(x + offset, y, w, h);

	while (file)
	{
		x = valueFromFile(file);
		y = valueFromFile(file);
		w = valueFromFile(file);
		h = valueFromFile(file);

		this->addObject(x + offset, y, w, h);
	}
}


void Window::loadRandomScene()
{	
	if (this->objectSpeed == 1)
	{
		int amountOfScenes = 5;
		if (this->index == -1)
			this->loadObjectsFromFile("resources/scene" + std::to_string((rand() % (amountOfScenes - 1 + 1)) + 1) + ".txt");
		this->loadObjectsFromFile("resources/scene" + std::to_string((rand() % (amountOfScenes - 1 + 1)) + 1) + ".txt");
	}
	else
	{
		int amountOfDScenes = 5;
		if (this->index == -1)
			this->loadObjectsFromFile("resources/dscene" + std::to_string((rand() % (amountOfDScenes - 1 + 1)) + 1) + ".txt");
		this->loadObjectsFromFile("resources/dscene" + std::to_string((rand() % (amountOfDScenes - 1 + 1)) + 1) + ".txt");
	}
}


bool Window::updateObjects(Player &player)
{
	for (std::vector<Object>::size_type i = 0; i < this->objects.size(); i++)
	{
		this->objects[i].rect.x -= this->objectSpeed;
		if (this->objects[i].rect.x < 0 - this->objects[i].rect.w)
		{
			this->objects.erase(this->objects.begin() + i);
			this->index--;
			if (this->index == 0)
			{
				this->index = this->objects.size();
				this->loadRandomScene();
			}
		}
		else
		{
			if (this->objects[i].checkPlayerCollision(player))
			{
				player.rect.x -= this->objectSpeed;
				if (player.rect.x <= 0)
					return true;
			}
		}
	}
	return false;
}


void Window::renderObjects()
{
	for (const Object& obj : this->objects)
	{
		this->renderRect(obj);
	}
}