
#include "../Header-Files-Folder/interface-files-includer.h"

Input input_screen_point(Point* point, Screen screen, const Bounds sBounds, Field mineField, const Bounds fBounds)
{
  Point inputPoint = {-1, -1};

  Input inputEvent = INPUT_NONE;

  Event event;

  while(!point_inside_bounds(inputPoint, fBounds))
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
        inputPoint = parse_mouse_point(event, sBounds, fBounds);

        inputEvent = INPUT_UNLOCK;
      }
      else if(event.button.button == SDL_BUTTON_RIGHT)
      {
        inputPoint = parse_mouse_point(event, sBounds, fBounds);

        inputEvent = INPUT_FLAG;

        break;
      }
    }
  }

  *point = inputPoint;

  return inputEvent;
}

Point parse_mouse_point(const Event event, const Bounds sBounds, const Bounds fBounds)
{
  const double squareHeight = (sBounds.height / fBounds.height);
  const double squareWidth = (sBounds.width / fBounds.width);

  int width = floor( (double) event.motion.x / squareWidth);
  int height = floor( (double) event.motion.y / squareHeight);

  return (Point) {height, width};
}
