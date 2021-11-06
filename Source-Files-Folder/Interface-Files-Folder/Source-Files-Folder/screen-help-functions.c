
#include "../Header-Files-Folder/interface-files-includer.h"

bool setup_display_screen(Window** window, Renderer** renderer, Surface** surface, const int height, const int width, char title[])
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}

	if(IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Quit();

		return false;
	}

	if(!create_screen_window(window, height, width, title))
	{
		SDL_Quit();

		return false;
	}

	if(!create_window_surface(surface, *window))
	{
		SDL_DestroyWindow(*window);

		SDL_Quit();

		return false;
	}

	if(!create_surface_renderer(renderer, *surface))
	{
		SDL_FreeSurface(*surface);

		SDL_DestroyWindow(*window);

		SDL_Quit();

		return false;
	}

	return true;
}

bool create_surface_texture(Texture** texture, Renderer* renderer, Surface* surface)
{
  *texture = SDL_CreateTextureFromSurface(renderer, surface);

	return (texture != NULL);
}

bool create_surface_renderer(Renderer** renderer, Surface* surface)
{
  *renderer = SDL_CreateSoftwareRenderer(surface);

	return (*renderer != NULL);
}

bool create_window_surface(Surface** surface, Window* window)
{
  *surface = SDL_GetWindowSurface(window);

	return (*surface != NULL);
}

bool create_screen_window(Window** window, const int height, const int width, char title[])
{
  *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, height, width, 0);

	return (*window != NULL);
}

void free_display_screen(Window* window, Renderer* renderer, Surface* surface)
{
	SDL_DestroyRenderer(renderer);

	SDL_FreeSurface(surface);

	SDL_DestroyWindow(window);

	SDL_Quit();
}
