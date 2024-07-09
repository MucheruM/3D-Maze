#ifndef GLOBAL_H
#define GLOBAL_H

/* render window */
extern SDL_Window *window;

/* window renderer */
extern SDL_Renderer *renderer;

/* texture */
extern SDL_Texture *texture;

/* buffer for textures */
extern uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

/* array of textures */
extern uint32_t tiles[TEX_COUNT][TEX_HEIGHT][TEX_WIDTH];

/* X and Y start position */
extern point_t pos;

/* initial direction vector */
extern point_t dir;

/* camera plane */
extern point_t plane;

/* time of current frame */
extern double current_time;

/* rain effect variables */
extern bool rain_active;
extern Uint32 rain_toggle_time;
extern Uint32 rain_interval;

#endif /* GLOBAL_H */
