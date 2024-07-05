#include "maze.h"
#include <stdio.h>  // Add for debug logging

/* global variables */
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
uint32_t tiles[TEX_COUNT][TEX_HEIGHT][TEX_WIDTH];
point_t pos;
point_t dir;
point_t plane;
double time;

/**
 * main - renders maze
 * @argc: number of arguments
 * @argv: pointer to array of arguments
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
        int *maze; /* 2D array defining maze map */
        char *mapName;
        bool textured;

        /* initial values for global variables */
        pos.x = 1;
        pos.y = 12;
        dir.x = 1;
        dir.y = -0.66;
        plane.x = 0;
        plane.y = 0.66;
        time = 0;

        /* check user arguments and set options */
        mapName = "\0";
        textured = true;
        if (argc == 3)
        {
                if (strcmp(argv[2], "no_tex") == 0)
                        textured = false;
                mapName = argv[1];
        }
        else if (argc == 2)
        {
                if (strcmp(argv[1], "no_tex") == 0)
                {
                        mapName = "maps/map_0";
                        textured = false;
                }
                else
                        mapName = argv[1];
        }
        else if (argc == 1)
                mapName = "maps/map_0";

        /* start SDL and create window and renderer */
        printf("Initializing SDL...\n");
        if (!initSDL())
        {
                fprintf(stderr, "Failed to initialize SDL\n");
                return (1);
        }
        printf("SDL initialized successfully\n");

        /* parse maze file */
        printf("Parsing maze map...\n");
        maze = NULL;
        maze = parseMap(mapName, maze);
        if (maze == NULL)
        {
                fprintf(stderr, "Failed to parse maze map\n");
                return (1);
        }
        printf("Maze map parsed successfully\n");

        if (textured)
        {
                printf("Loading textures...\n");
		loadTextures(mapName);
                printf("Textures loaded successfully\n");
        }

        /* loops until user exits by ESC or closing window */
        while (!quit())
        {
                if (!textured)
                        renderBGFlat();

                /* draw walls, textured floor, and textured ceiling */
                raycaster(maze, textured);

                /* handles user input */
                input(maze);
        }

        /* close SDL, renderer, and window */
        printf("Closing SDL...\n");
        closeSDL();
        free(maze);
        printf("SDL closed successfully\n");
        return (0);
}

