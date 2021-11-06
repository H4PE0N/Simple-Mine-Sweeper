
#ifndef MINE_FIELD_HANDLER_H
#define MINE_FIELD_HANDLER_H

Square** create_field_matrix(const int, const int);

bool generate_mine_field(Field, const Bounds, const int);

int adjacent_field_mines(Field, const Bounds, const Point);

bool activate_field_mines(Field, const Bounds, const int);

bool mark_adjacent_mines(Field, const Bounds);

bool point_inside_bounds(const Point, const Bounds);

void free_mine_field(Square**, const int);

bool unlock_field_square(Field, const Bounds, const Point);

#endif
