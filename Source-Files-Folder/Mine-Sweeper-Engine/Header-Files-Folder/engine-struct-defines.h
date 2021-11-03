
#ifndef ENGINE_STRUCT_DEFINES_H
#define ENGINE_STRUCT_DEFINES_H

typedef struct Square
{
  bool mine;
  bool visable;
  bool flagged;
  int adjacent;
} Square;

typedef Square** Field;

#endif
