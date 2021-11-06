
#ifndef SCREEN_HELP_FUNCTIONS_H
#define SCREEN_HELP_FUNCTIONS_H

bool create_screen_window(Window**, const int, const int, char[]);

bool create_window_surface(Surface**, Window*);

bool create_surface_renderer(Renderer**, Surface*);

bool create_surface_texture(Texture**, Renderer*, Surface*);

bool setup_display_screen(Window**, Renderer**, Surface**, const int, const int, char[]);

void free_display_screen(Window*, Renderer*, Surface*);

#endif
