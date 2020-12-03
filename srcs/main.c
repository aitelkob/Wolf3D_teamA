/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:27:40 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/12/03 20:13:40 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

/*
**	Time it took to draw this frame
**	Frame per second
**	Speed of movement and rotation
**	Square per second
**	Radient per second
*/

void sdl_quit(t_wolf_3d *w)
{
	SDL_FreeSurface(w->sdl.cur);
	SDL_DestroyRenderer(w->sdl.renderer);
	SDL_DestroyWindow(w->sdl.win);
	SDL_Quit();
}

void update(t_wolf_3d *w)
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), (w->fps.last_frame_time + w->fps.frame_target)))
		;
	w->fps.delta_time = (SDL_GetTicks() - w->fps.last_frame_time) / 1000.0f;
	w->fps.last_frame_time = SDL_GetTicks();
	w->fps.movespeed = 3 * w->fps.delta_time;
	w->fps.rotspeed = 2 * w->fps.delta_time;
}

void		imga_copy(t_wolf_3d *w)
{
	SDL_UpdateTexture(w->sdl.texture, NULL, w->data, WIDTH * sizeof(int));
	SDL_RenderCopy(w->sdl.renderer, w->sdl.texture, NULL, NULL);
}

void render(t_wolf_3d *w)
{
	SDL_SetRenderDrawColor(w->sdl.renderer, 0, 0, 0, 255);
	SDL_RenderClear(w->sdl.renderer);

	draw_map_3d(w);
	imga_copy(w);
	image_clear(w);
	mini_map(w);
	mini_player(w);
	SDL_RenderPresent(w->sdl.renderer);
}

/*
**	Start the Mouse postion in the middle of the window
*/

void game_engine(t_wolf_3d *w)
{
	////    game loop //////
	while (w->game_running == 0)
	{
		process_input(w, w->player.world_map);
		update(w);
		render(w);
	}
}

/*
** Load the map from the file
*/

void Load_map(t_wolf_3d *w, char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	if (fd >= 3)
		w->player.world_map = get_map(w->player.world_map, fd, av);
	else
		show_error1();
}

int main(int ac, char **av)
{
	t_wolf_3d *w;

	if (ac == 2)
	{
		w = malloc(sizeof(t_wolf_3d));
		Load_map(w, av);
		w->game_running = sdl_init_win(w);
		init_perso(w);
		game_engine(w);
		sdl_quit(w);
		free_map2(w->player.world_map, 24);
		free(w->data);
		free(w->sdl.new_text);
		free(w);
		w = NULL;
	}
	else if (ac == 1)
		show_error3();
	return (0);
}
