/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 01:41:22 by yait-el-          #+#    #+#             */
/*   Updated: 2020/12/05 04:07:03 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

void		free_map(char **map, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void		free_map2(int **map, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void		free_surface(t_wolf_3d *w)
{
	SDL_FreeSurface(w->sdl.cur);
	SDL_FreeSurface(w->sdl.wall);
	SDL_FreeSurface(w->sdl.wall1);
	SDL_FreeSurface(w->sdl.wall2);
	SDL_FreeSurface(w->sdl.wall3);
	SDL_FreeSurface(w->sdl.wall4);
	SDL_FreeSurface(w->sdl.wall5);
	SDL_FreeSurface(w->sdl.ceiling_texture);
	SDL_FreeSurface(w->sdl.roof_texture);
}

void		sdl_quit(t_wolf_3d *w)
{
	SDL_DestroyRenderer(w->sdl.renderer);
	SDL_DestroyWindow(w->sdl.win);
	free(w);
	SDL_Quit();
}
