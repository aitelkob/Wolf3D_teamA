/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:02:13 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/12/06 02:32:03 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

/*
 ** Creating a Window centered in the middle of the screen
*/

int			sdl_init_win(t_wolf_3d *w)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	w->sdl.win = SDL_CreateWindow("Wolf_3D", SDL_WINDOWPOS_CENTERED
			, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (!w->sdl.win)
		return (1);
	sdl_init_texture(w);
	return (0);
}

int			sdl_init_texture(t_wolf_3d *w)
{
	sdl_init_render(w);
	w->sdl.texture = SDL_CreateTexture(w->sdl.renderer
			, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING
			, WIDTH, HEIGHT);
	if (!w->sdl.texture)
		return (1);
	if(TTF_Init()==-1) 
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		return(1);
	}
	return (0);
}

int			sdl_init_render(t_wolf_3d *w)
{
	w->sdl.renderer = SDL_CreateRenderer(w->sdl.win, -1
			, SDL_RENDERER_ACCELERATED);
	if (!w->sdl.renderer)
		return (1);
	return (0);
}
