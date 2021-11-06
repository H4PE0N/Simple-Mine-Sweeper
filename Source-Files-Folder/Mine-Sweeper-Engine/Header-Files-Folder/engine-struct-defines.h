
#ifndef ENGINE_STRUCT_DEFINES_H
#define ENGINE_STRUCT_DEFINES_H

typedef struct Square
{
  bool mine;
  bool visable;
  bool flagged;
  int adjacent;
} Square;

typedef struct Point
{
  int height;
  int width;
} Point;

typedef struct Bounds
{
  int height;
  int width;
} Bounds;

typedef Square** Field;

#endif
