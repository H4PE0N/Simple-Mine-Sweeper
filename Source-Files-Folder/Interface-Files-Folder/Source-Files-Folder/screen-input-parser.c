
#include "../Header-Files-Folder/interface-files-includer.h"

Input input_screen_point(Point* point, Screen screen, Field mineField, const Board board)
{
  Point inputPoint = {-1, -1};

  Input inputEvent = INPUT_NONE;

  Event event;

  while(!point_inside_board(inputPoint, board))
  {
    if(!SDL_PollEvent(&event)) continue;

    if(event.type == SDL_QUIT)
    {
      inputEvent = INPUT_QUIT;

      return inputEvent;
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      if(event.button.button == SDL_BUTTON_LEFT)
      {
        inputPoint = parse_mouse_point(event, screen, board);

        inputEvent = INPUT_UNLOCK;
      }
      else if(event.button.button == SDL_BUTTON_RIGHT)
      {
        inputPoint = parse_mouse_point(event, screen, board);

        inputEvent = INPUT_FLAG;

        break;
      }
    }
  }

  *point = inputPoint;

  return inputEvent;
}

Point parse_mouse_point(const Event event, Screen screen, const Board board)
{
  const double squareHeight = (screen.height / board.height);
  const double squareWidth = (screen.width / board.width);

  int width = floor( (double) event.motion.x / squareWidth);
  int height = floor( (double) event.motion.y / squareHeight);

  return (Point) {height, width};
}
