
#include "../Header-Files-Folder/game-files-includer.h"

int main(int argAmount, char* arguments[])
{
  Field mineField = create_mine_field(10, 10);

  mineField[0][0].mine = true;

  free_mine_field(mineField, 10);

  return false;
}
