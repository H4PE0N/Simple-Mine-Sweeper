
#include "../Header-Files-Folder/game-files-includer.h"

int main(int argAmount, char* arguments[])
{
  srand(time(NULL));

  const Bounds sBounds = {800, 800};
  const char title[] = "Test Title\n";

  const Bounds fBounds = {10, 10};
  const int mines = 10;

  Field mineField = create_field_matrix(fBounds.height, fBounds.width);

  if(!generate_mine_field(mineField, fBounds, mines))
  {
    printf("Could not generate field!\n");

    free_mine_field(mineField, fBounds.height);

    return false;
  }

  Screen screen;

  if(!setup_display_screen(&screen, sBounds, title))
  {
    printf("Could not setup_display_screen!\n");

    return false;
  }

  bool result = false;

  if(mine_sweeper_game(&result, screen, sBounds, mineField, fBounds))
  {
    if(!render_mine_field(screen.renderer, sBounds, mineField, fBounds))
    {
      printf("Could not render_mine_field!\n");

      return false;
    }
    SDL_UpdateWindowSurface(screen.window);

    if(result)
    {
      printf("You have won the game!\n");
    }
    else
    {
      printf("You have lost the game!\n");
    }

    Event event;

    while(event.type != SDL_QUIT)
    {
      SDL_PollEvent(&event);
    }
  }
  else
  {
    printf("The game was quitted!\n");
  }

  free_mine_field(mineField, fBounds.height);

  free_display_screen(screen);

  return false;
}

bool game_still_running(bool* result, Field mineField, const Bounds fBounds)
{
  if(mine_field_cleared(mineField, fBounds))
  {
    *result = true;

    flag_field_mines(mineField, fBounds);

    return false;
  }

  else if(mine_field_exposed(mineField, fBounds))
  {
    *result = false;

    unlock_field_mines(mineField, fBounds);

    return false;
  }

  return true;
}

bool mine_sweeper_game(bool* result, Screen screen, const Bounds sBounds, Field mineField, const Bounds fBounds)
{
  while(game_still_running(result, mineField, fBounds))
  {
    if(!render_mine_field(screen.renderer, sBounds, mineField, fBounds))
    {
      printf("Could not render_mine_field!\n");

      return false;
    }
    SDL_UpdateWindowSurface(screen.window);


    Point point = {-1, -1};

    Input inputEvent = input_screen_point(&point, screen, sBounds, mineField, fBounds);

    if(inputEvent == INPUT_QUIT)
    {
      printf("Exiting the window manually!\n");

      return false;
    }
    else if(inputEvent == INPUT_UNLOCK)
    {
      if(!unlock_field_square(mineField, fBounds, point))
      {
        printf("Could not unlock_field_square!\n");
      }
    }
    else if(inputEvent == INPUT_FLAG)
    {
      if(!flag_field_square(mineField, fBounds, point))
      {
        printf("Could not flag_field_square!\n");
      }
    }
  }
  printf("The game was played normaly!\n");

  return true;
}
