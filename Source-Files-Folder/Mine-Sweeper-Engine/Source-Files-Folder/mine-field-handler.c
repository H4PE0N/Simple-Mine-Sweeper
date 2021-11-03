
#include "../Header-Files-Folder/engine-files-includer.h"

Field create_mine_field(const int height, const int width)
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

void free_mine_field(Field mineField, const int height)
{
  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    free(mineField[hIndex]);
  }

  free(mineField);
}
