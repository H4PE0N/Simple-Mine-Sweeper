
#include "../Header-Files-Folder/game-files-includer.h"

int main(int argAmount, char* arguments[])
{
  const Bounds sBounds = {800, 800};
  const char title[] = "Test Title\n";

  const Bounds fBounds = {10, 10};
  const int mines = 20;

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

  if(mine_sweeper_game(screen, sBounds, mineField, fBounds))
  {
    printf("You have won the game!\n");
  }
  else
  {
    printf("You have lost the game!\n");
  }

  if(!render_mine_field(screen.renderer, sBounds, mineField, fBounds))
  {
    printf("Could not render_mine_field!\n");

    return false;
  }

  SDL_UpdateWindowSurface(screen.window);

  getchar();

  free_mine_field(mineField, fBounds.height);
  free_display_screen(screen);

  return false;
}

bool mine_sweeper_game(Screen screen, const Bounds sBounds, Field mineField, const Bounds fBounds)
{
  while(!mine_field_cleared(mineField, fBounds))
  {
    if(mine_field_exposed(mineField, fBounds))
    {
      printf("mine_field_exposed!\n");

      return false;
    }

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
  return true;
}
