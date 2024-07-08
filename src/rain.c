#include "maze.h"
#include "global.h"

void renderRain()
{
    // Set the color for the raindrops (white in this example)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw a number of raindrop lines at random positions
    for (int i = 0; i < 100; i++) // Adjust number of drops as needed
    {
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        SDL_RenderDrawLine(renderer, x, y, x, y + 10); // Draws a line 10 pixels long
    }
}

