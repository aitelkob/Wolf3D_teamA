/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:27:40 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/12/05 02:45:13 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

/*
 **	Game loop
*/

void	game_engine(t_wolf_3d *w)
{
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

void	load_map(t_wolf_3d *w, char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	if (fd >= 3)
		w->player.world_map = get_map(w->player.world_map, fd, av);
	else
		show_error1();
}

int		main(int ac, char **av)
{
	t_wolf_3d *w;

	if (ac == 2)
	{
		w = malloc(sizeof(t_wolf_3d));
		load_map(w, av);
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
