
#include "../Header-Files-Folder/game-files-includer.h"

int main(int argAmount, char* arguments[])
{
  const int height = 10, width = 10, mines = 20;

  Field mineField = create_field_matrix(height, width);

  if(!generate_mine_field(mineField, height, width, mines))
  {
    printf("Could not generate field!\n");

    free_mine_field(mineField, height);

    return false;
  }

  if(mine_sweeper_game(mineField, height, width, mines))
  {
    printf("You have won the game!\n");
  }
  else
  {
    printf("You have lost the game!\n");
  }

  free_mine_field(mineField, height);

  return false;
}

bool mine_sweeper_game(Field mineField, const int height, const int width, const int mines)
{
  Point point = {2, 2};

  if(!unlock_field_square(mineField, height, width, point))
  {
    printf("Could not unlock_field_square!\n");
  }

  for(int hIndex = 0; hIndex < height; hIndex += 1)
  {
    for(int wIndex = 0; wIndex < width; wIndex += 1)
    {
      Square square = mineField[hIndex][wIndex];

      if(square.flagged)
      {
        printf("F ");
      }
      else if(square.visable && !square.mine)
      {
        printf("%d ", square.adjacent);
      }
      else if(square.visable && square.mine)
      {
        printf("M ");
      }
      else
      {
        printf(". ");
      }
    }
    printf("\n");
  }

  return true;
}
