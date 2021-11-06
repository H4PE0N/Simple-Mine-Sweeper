
#include "../Header-Files-Folder/interface-files-includer.h"

bool setup_display_screen(Screen* screen, const Bounds sBounds, const char title[])
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

	if(!create_screen_window(&screen->window, sBounds.height, sBounds.width, title))
	{
		SDL_Quit();

		return false;
	}

	if(!create_window_surface(&screen->surface, screen->window))
	{
		SDL_DestroyWindow(screen->window);

		SDL_Quit();

		return false;
	}

	if(!create_surface_renderer(&screen->renderer, screen->surface))
	{
		SDL_FreeSurface(screen->surface);

		SDL_DestroyWindow(screen->window);

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

bool create_screen_window(Window** window, const int height, const int width, const char title[])
{
  *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, height, width, 0);

	return (*window != NULL);
}

void free_display_screen(Screen screen)
{
	SDL_DestroyRenderer(screen.renderer);

	SDL_FreeSurface(screen.surface);

	SDL_DestroyWindow(screen.window);

	SDL_Quit();
}

bool render_mine_field(Renderer* renderer, const Bounds sBounds, Field mineField, const Bounds fBounds)
{
  for(int hIndex = 0; hIndex < fBounds.height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < fBounds.width; wIndex += 1)
    {
      const Square square = mineField[hIndex][wIndex];
      const Point point = {hIndex, wIndex};

      if(!render_field_square(renderer, sBounds, fBounds, point, square))
      {
        printf("Could not render_field_square!\n");

        return false;
      }

      if(!render_field_symbol(renderer, sBounds, fBounds, point, square))
      {
        printf("Could not render_field_symbol!\n");

        return false;
      }
    }
  }

  SDL_RenderPresent(renderer);

  return true;
}

bool render_field_square(Renderer* renderer, const Bounds sBounds, const Bounds fBounds, const Point point, const Square square)
{
  Surface* image = NULL;

  if(!extract_square_image(&image, square))
  {
    printf("Could not extract_square_image!\n");

    return false;
  }

  Rect position;

  if(!screen_field_position(&position, sBounds, fBounds, point))
  {
    SDL_FreeSurface(image);

    return false;
  }

  if(!render_surface_texture(renderer, image, position))
  {
    SDL_FreeSurface(image);

    return false;
  }

  SDL_FreeSurface(image);

  return true;
}

bool screen_field_position(Rect* position, const Bounds sBounds, const Bounds fBounds, const Point point)
{
  if(!point_inside_bounds(point, fBounds)) return false;

  const int squareHeight = (sBounds.height / fBounds.height);
  const int squareWidth = (sBounds.width / fBounds.width);

  const int screenHeight = (squareHeight * point.height);
  const int screenWidth = (squareWidth * point.width);

  *position = (Rect) {screenWidth, screenHeight, squareWidth, squareHeight};

  return true;
}

bool render_field_symbol(Renderer* renderer, const Bounds sBounds, const Bounds fBounds, const Point point, const Square square)
{
  Surface* image = NULL;

  if(!extract_symbol_image(&image, square))
  {
    printf("Could not extract_symbol_image!\n");

    return false;
  }

  // If the image is NULL, but the function returned true anyways.
  if(image == NULL)
  {
    // This means that the function returned an empty image (blank)
    return true;
  }

  Rect position;

  if(!screen_field_position(&position, sBounds, fBounds, point))
  {
    SDL_FreeSurface(image);

    return false;
  }

  if(!render_surface_texture(renderer, image, position))
  {
    SDL_FreeSurface(image);

    return false;
  }

  SDL_FreeSurface(image);

  return true;
}

bool extract_symbol_image(Surface** image, const Square square)
{
  char filename[200]; memset(filename, 0, 200);

  if(!extract_symbol_file(filename, square))
  {
    return false;
  }

  // If the function returned true but no filename
  if(strlen(filename) == 0)
  {
    // Returning true without extracting image (no image)
    return true;
  }

  *image = IMG_Load(filename);

  return (*image != NULL);
}

char* adjacentFiles[] = {"ONE_SYMBOL.png", "TWO_SYMBOL.png", "THREE_SYMBOL.png", "FOUR_SYMBOL.png", "FIVE_SYMBOL.png", "SIX_SYMBOL.png", "SEVEN_SYMBOL.png", "EIGHT_SYMBOL.png"};

bool extract_symbol_file(char* filename, const Square square)
{
  if(!square.visable && square.flagged)
  {
    sprintf(filename, "%s/%s", SCREEN_IMAGE_FOLDER, FLAGGED_SYMBOL_FILE);
  }
  else if(square.visable && square.adjacent != 0)
  {
    char* adjacentFile = adjacentFiles[square.adjacent - 1];

    sprintf(filename, "%s/%s", SCREEN_IMAGE_FOLDER, adjacentFile);
  }
  else if(square.visable && square.mine)
  {
    sprintf(filename, "%s/%s", SCREEN_IMAGE_FOLDER, MINE_SYMBOL_FILE);
  }
  return true;
}

bool extract_square_image(Surface** image, const Square square)
{
  char filename[200]; memset(filename, 0, 200);

  if(!extract_square_file(filename, square))
  {
    return false;
  }

  *image = IMG_Load(filename);

  return (*image != NULL);
}

bool extract_square_file(char* filename, const Square square)
{
  if(square.visable && !square.mine)
  {
    sprintf(filename, "%s/%s", SCREEN_IMAGE_FOLDER, VISABLE_SQUARE_FILE);
  }
  else if(square.visable && square.mine)
  {
    sprintf(filename, "%s/%s", SCREEN_IMAGE_FOLDER, EXPLODE_SQUARE_FILE);
  }
  else
  {
    sprintf(filename, "%s/%s", SCREEN_IMAGE_FOLDER, DEFAULT_SQUARE_FILE);
  }
  return true;
}

bool render_surface_texture(Renderer* renderer, Surface* surface, const Rect position)
{
	Texture* texture = NULL;

	if(!create_surface_texture(&texture, renderer, surface))
	{
		return false;
	}

	SDL_RenderCopy(renderer, texture, NULL, &position);

	SDL_DestroyTexture(texture);

	return true;
}
