#include "maze.h"

/**
 * input - checks user input for movement
 * @maze: 2D array defining maze map
 * Return: void
 */
void input(int *maze)
{
	const uint8_t *keystate; /* current key state */
	double oldTime; /* time of previous frame */
	double frameTime; /* time the frame has taken in seconds */
	double oldDirX, oldPlaneX; /* previous dir.x and plane.x */
	double moveSpeed; /* move speed modifier */
	double rotSpeed; /*rotation speed modifier */

	keystate = SDL_GetKeyboardState(NULL);
	oldTime = time;
	time = SDL_GetTicks();
	frameTime = (time - oldTime) / 1000.0;
	moveSpeed = frameTime * 5.0;
	rotSpeed = frameTime * 3.0;

	/* move forward if no wall in front */
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP])
	{
		if (!*((int *)maze + (int)(pos.x + dir.x * moveSpeed)
					* MAP_WIDTH + (int)pos.y))
			pos.x += dir.x * moveSpeed;
		if (!*((int *)maze + (int)pos.x * MAP_WIDTH +
			(int)(pos.y + dir.y * moveSpeed)))
			pos.y += dir.y * moveSpeed;
	}

	/* move backward if no wall behind */
	if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN])
	{
		if (!*((int *)maze + (int)(pos.x - dir.x * moveSpeed)
					* MAP_WIDTH + (int)pos.y))
			pos.x -= dir.x * moveSpeed;
		if (!*((int *)maze + (int)pos.x * MAP_WIDTH +
			(int)(pos.y - dir.y * moveSpeed)))
			pos.y -= dir.y * moveSpeed;
	}

	/* strafe left */
	if (keystate[SDL_SCANCODE_Q])
	{
		if (!*((int *)maze + (int)(pos.x - plane.x * moveSpeed)
					* MAP_WIDTH + (int)pos.y))
			pos.x -= plane.x * moveSpeed;
		if (!*((int *)maze + (int)pos.x * MAP_WIDTH +
			(int)(pos.y - plane.y * moveSpeed)))
			pos.y -= plane.y * moveSpeed;
	}

	/* strafe right */
	if (keystate[SDL_SCANCODE_E])
	{
		if (!*((int *)maze + (int)(pos.x + plane.x * moveSpeed)
					* MAP_WIDTH + (int)pos.y))
			pos.x += plane.x * moveSpeed;
		if (!*((int *)maze + (int)pos.x * MAP_WIDTH +
			(int)(pos.y + plane.y * moveSpeed)))
			pos.y += plane.y * moveSpeed;
	}

	/* rotate left */
	if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
	{
		/* rotate camera direction */
		oldDirX = dir.x;
		dir.x = dir.x * cos(rotSpeed) - dir.y * sin(rotSpeed);
		dir.y = oldDirX * sin(rotSpeed) + dir.y * cos(rotSpeed);

		/* rotate camera plane */
		oldPlaneX = plane.x;
		plane.x = plane.x * cos(rotSpeed) - plane.y * sin(rotSpeed);
		plane.y = oldPlaneX * sin(rotSpeed) + plane.y * cos(rotSpeed);
	}

	/* rotate right */
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
	{
		/* rotate camera direction */
		oldDirX = dir.x;
		dir.x = dir.x * cos(-rotSpeed) - dir.y * sin(-rotSpeed);
		dir.y = oldDirX * sin(-rotSpeed) + dir.y * cos(-rotSpeed);

		/* rotate camera plane */
		oldPlaneX = plane.x;
		plane.x = plane.x * cos(-rotSpeed) - plane.y * sin(-rotSpeed);
		plane.y = oldPlaneX * sin(-rotSpeed) + plane.y * cos(-rotSpeed);
	}
}

/**
 * quit - checks if user quits
 * Return: True if user quits, otherwise False
 */
bool quit(void)
{
	SDL_Event event; /* event listener */
	bool quit;
	uint32_t windowFlags;

	quit = false;
	while (SDL_PollEvent(&event) != 0)
	{
		/* if window's close button is pressed */
		if (event.type == SDL_QUIT)
			quit = true;

		/* if ESC is pressed */
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			quit = true;

		/* toggles between windowed and fullscreens */
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
		{
			windowFlags = SDL_GetWindowFlags(window);
			if (windowFlags & SDL_WINDOW_FULLSCREEN)
				SDL_SetWindowFullscreen(window, SDL_FALSE);
			else
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		}
	}

	return (quit);
}
