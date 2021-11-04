
#include "../Header-Files-Folder/engine-files-includer.h"

bool mine_field_cleared(Field mineField, const int height, const int width)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      Square square = mineField[hIndex][wIndex];

      // If an empty square is not visable, the minefield is not cleared
      if(!square.mine && !square.visable) return false;

      // If a mine is visable, the minefield is not cleared
      if(square.mine && square.visable) return false;
    }
  }
  return true;
}

bool mine_field_exposed(Field mineField, const int height, const int width)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      Square square = mineField[hIndex][wIndex];

      if(square.mine && square.visable) return true;
    }
  }
  return false;
}

bool unlock_field_square(Field mineField, const int height, const int width, const Point point)
{
  if(!point_inside_bounds(point, height, width)) return false;


  Square square = mineField[point.height][point.width];

  if(square.flagged) return false;


	mineField[point.height][point.width].visable = true;


	if(square.adjacent != 0 || square.mine) return true;


  for(int hIndex = (point.height - 1); hIndex <= (point.height + 1); hIndex += 1)
	{
		for(int wIndex = (point.width - 1); wIndex <= (point.width + 1); wIndex += 1)
		{
      Point currPoint = {hIndex, wIndex};

			if(!point_inside_bounds(currPoint, height, width)) continue;


      Square currSquare = mineField[hIndex][wIndex];


			if(currSquare.flagged) continue;

      if(currSquare.visable) continue;


			if(!unlock_field_square(mineField, height, width, currPoint))
      {
        // The program should never have to go here!

        return false;
      }
		}
	}

	return true;
}

Field create_field_matrix(const int height, const int width)
{
  Field mineField = malloc(sizeof(Square*) * height);

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    mineField[hIndex] = malloc(sizeof(Square) * width);

    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      Square square = {false, false, false, 0};

      mineField[hIndex][wIndex] = square;
    }
  }

  return mineField;
}

bool generate_mine_field(Field mineField, const int height, const int width, const int mines)
{
  if(!activate_field_mines(mineField, height, width, mines)) return false;

  if(!mark_adjacent_mines(mineField, height, width)) return false;

  return true;
}

bool activate_field_mines(Field mineField, const int height, const int width, const int mines)
{
  mineField[4][4].mine = true;

  mineField[5][5].mine = true;

  return true;
}

bool mark_adjacent_mines(Field mineField, const int height, const int width)
{
  for(int hIndex = 0; hIndex < height; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < width; wIndex = wIndex + 1)
		{
			if(mineField[hIndex][wIndex].mine) continue;

			Point point = {hIndex, wIndex};
			int adjacent = adjacent_field_mines(mineField, height, width, point);

			mineField[hIndex][wIndex].adjacent = adjacent;
		}
	}
  return true;
}

int adjacent_field_mines(Field mineField, const int height, const int width, const Point point)
{
	int adjacent = 0;

	for(int hIndex = (point.height - 1); hIndex <= (point.height + 1); hIndex += 1)
	{
		for(int wIndex = (point.width - 1); wIndex <= (point.width + 1); wIndex += 1)
		{
      Point point = {hIndex, wIndex};

			if(!point_inside_bounds(point, height, width)) continue;

			if(mineField[hIndex][wIndex].mine) adjacent += 1;
		}
	}
	return adjacent;
}

bool point_inside_bounds(const Point point, const int height, const int width)
{
  bool hInside = (point.height >= 0 && point.height < height);
  bool wInside = (point.width >= 0 && point.width < width);

	return (hInside && wInside);
}

void free_mine_field(Field mineField, const int height)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    free(mineField[hIndex]);
  }

  free(mineField);
}
