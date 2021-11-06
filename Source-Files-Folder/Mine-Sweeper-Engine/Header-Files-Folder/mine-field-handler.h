
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

bool flag_field_square(Field, const Bounds, const Point);

bool mine_field_cleared(Field, const Bounds);

bool mine_field_exposed(Field, const Bounds);

void unlock_field_mines(Field, const Bounds);

void flag_field_mines(Field, const Bounds);

bool delete_array_point(Point*, const int, const int);

Point* every_field_point(const int, const int);

#endif
