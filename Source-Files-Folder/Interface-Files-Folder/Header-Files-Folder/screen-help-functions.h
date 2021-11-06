
#ifndef SCREEN_HELP_FUNCTIONS_H
#define SCREEN_HELP_FUNCTIONS_H

bool create_screen_window(Window**, const int, const int, const char[]);

bool create_window_surface(Surface**, Window*);

bool create_surface_renderer(Renderer**, Surface*);

bool create_surface_texture(Texture**, Renderer*, Surface*);

bool setup_display_screen(Screen*, const Bounds, const char[]);

void free_display_screen(Screen);

bool color_point_square(Renderer*, const Bounds, const Bounds, const Point, const Color);

bool render_field_square(Renderer*, const Bounds, const Bounds, const Point, const Square);

bool render_field_symbol(Renderer*, const Bounds, const Bounds, const Point, const Square);

bool render_mine_field(Renderer*, const Bounds, Field, const Bounds);

bool render_surface_texture(Renderer*, Surface*, const Rect);

bool extract_square_file(char*, const Square);

bool extract_square_image(Surface**, const Square);

bool screen_field_position(Rect*, const Bounds, const Bounds, const Point);

bool extract_symbol_image(Surface**, const Square);

bool extract_symbol_file(char*, const Square);

#endif
