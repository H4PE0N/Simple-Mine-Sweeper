
#include "../Header-Files-Folder/engine-files-includer.h"

bool mine_field_cleared(Field mineField, const Bounds bounds)
{
  for(int hIndex = 0; hIndex < bounds.height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < bounds.width; wIndex += 1)
    {
      Square square = mineField[hIndex][wIndex];

      // If an empty square is not visable, the minefield is not cleared
      if(!square.mine && !square.visable) return false;

      // // If a mine is visable, the minefield is not cleared
      // if(square.mine && square.visable) return false;
    }
  }
  return true;
}

void flag_field_mines(Field mineField, const Bounds bounds)
{
  for(int hIndex = 0; hIndex < bounds.height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < bounds.width; wIndex += 1)
    {
      // Point point = {hIndex, wIndex};

      Square square = mineField[hIndex][wIndex];

      if(!square.mine) continue;

      // if(!unlock_field_square(mineField, bounds, point))
      // {
      //
      // }

      mineField[hIndex][wIndex].flagged = true;
    }
  }
}

void unlock_field_mines(Field mineField, const Bounds bounds)
{
  for(int hIndex = 0; hIndex < bounds.height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < bounds.width; wIndex += 1)
    {
      // Point point = {hIndex, wIndex};

      Square square = mineField[hIndex][wIndex];

      if(!square.mine) continue;

      // if(!unlock_field_square(mineField, bounds, point))
      // {
      //
      // }

      mineField[hIndex][wIndex].visable = true;
    }
  }
}

bool mine_field_exposed(Field mineField, const Bounds bounds)
{
  for(int hIndex = 0; hIndex < bounds.height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < bounds.width; wIndex += 1)
    {
      Square square = mineField[hIndex][wIndex];

      if(square.mine && square.visable) return true;
    }
  }
  return false;
}

bool flag_field_square(Field mineField, const Bounds bounds, const Point point)
{
  if(!point_inside_bounds(point, bounds)) return false;

  const Square square = mineField[point.height][point.width];

  if(square.visable) return false;

  // This inverts the value (flips the value on and off)
  mineField[point.height][point.width].flagged = !square.flagged;

  return true;
}

bool unlock_field_square(Field mineField, const Bounds bounds, const Point point)
{
  if(!point_inside_bounds(point, bounds)) return false;


  const Square square = mineField[point.height][point.width];

  if(square.flagged) return false;


	mineField[point.height][point.width].visable = true;


	if(square.adjacent != 0 || square.mine) return true;


  for(int hIndex = (point.height - 1); hIndex <= (point.height + 1); hIndex += 1)
	{
		for(int wIndex = (point.width - 1); wIndex <= (point.width + 1); wIndex += 1)
		{
      const Point currPoint = {hIndex, wIndex};

			if(!point_inside_bounds(currPoint, bounds)) continue;


      const Square currSquare = mineField[hIndex][wIndex];


			if(currSquare.flagged) continue;

      if(currSquare.visable) continue;


			if(!unlock_field_square(mineField, bounds, currPoint))
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

bool generate_mine_field(Field mineField, const Bounds bounds, const int mines)
{
  if(!activate_field_mines(mineField, bounds, mines)) return false;

  if(!mark_adjacent_mines(mineField, bounds)) return false;

  return true;
}

bool activate_field_mines(Field mineField, const Bounds bounds, const int mines)
{
  const int total = (bounds.height * bounds.width);

	if(mines >= total) return false;


	Point* points = every_field_point(bounds.height, bounds.width);


	for(int index = 0; index < mines; index = index + 1)
	{
		const int random = rand() % (total - index);

		const Point point = points[random];

		mineField[point.height][point.width].mine = true;

		if(!delete_array_point(points, (total - index), random))
    {

    }
	}

	free(points);

  return true;
}

bool delete_array_point(Point* points, const int amount, const int start)
{
  if(start < 0 || start >= amount) return false;

	for(int index = start; index < (amount - 1); index = index + 1)
	{
		points[index] = points[index + 1];
	}

  return true;
}

Point* every_field_point(const int height, const int width)
{
	const int total = (height * width);

	Point* points = malloc(sizeof(Point) * total);

	for(int hIndex = 0; hIndex < height; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < width; wIndex = wIndex + 1)
		{
			const int index = (hIndex * width) + wIndex;

			points[index] = (Point) {hIndex, wIndex};
		}
	}
	return points;
}


bool mark_adjacent_mines(Field mineField, const Bounds bounds)
{
  for(int hIndex = 0; hIndex < bounds.height; hIndex = hIndex + 1)
	{
		for(int wIndex = 0; wIndex < bounds.width; wIndex = wIndex + 1)
		{
			if(mineField[hIndex][wIndex].mine) continue;

			const Point point = {hIndex, wIndex};
			const int adjacent = adjacent_field_mines(mineField, bounds, point);

			mineField[hIndex][wIndex].adjacent = adjacent;
		}
	}
  return true;
}

int adjacent_field_mines(Field mineField, const Bounds bounds, const Point point)
{
	int adjacent = 0;

	for(int hIndex = (point.height - 1); hIndex <= (point.height + 1); hIndex += 1)
	{
		for(int wIndex = (point.width - 1); wIndex <= (point.width + 1); wIndex += 1)
		{
      const Point point = {hIndex, wIndex};

			if(!point_inside_bounds(point, bounds)) continue;

			if(mineField[hIndex][wIndex].mine) adjacent += 1;
		}
	}
	return adjacent;
}

bool point_inside_bounds(const Point point, const Bounds bounds)
{
  const bool hInside = (point.height >= 0 && point.height < bounds.height);
  const bool wInside = (point.width >= 0 && point.width < bounds.width);

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
