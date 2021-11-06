
#ifndef SCREEN_INPUT_PARSER_H
#define SCREEN_INPUT_PARSER_H

Input input_screen_point(Point*, Screen, const Bounds, Field, const Bounds);

Point parse_mouse_point(const Event, const Bounds, const Bounds);

#endif
