/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 04:06:04 by yait-el-          #+#    #+#             */
/*   Updated: 2020/12/08 04:26:11 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

void		mouse_limitation(t_wolf_3d *w)
{
	if (w->event.newmouse.x > WIDTH - 10)
	{
		SDL_WarpMouseInWindow(w->sdl.win, (WIDTH / 2), w->event.newmouse.y);
		w->event.newmouse.x = WIDTH / 2;
		w->event.oldmouse.x = WIDTH / 2;
	}
	else if (w->event.newmouse.x < 10)
	{
		SDL_WarpMouseInWindow(w->sdl.win, (WIDTH / 2), w->event.newmouse.y);
		w->event.newmouse.x = WIDTH / 2;
		w->event.oldmouse.x = WIDTH / 2;
	}
	else if (w->event.newmouse.y >= HEIGHT - 50)
		SDL_WarpMouseInWindow(w->sdl.win, w->event.oldmouse.x, HEIGHT - 60);
}

void		track_mouse(t_wolf_3d *w, Uint32 *mousestates)
{
	static int i;

	if (i == 0)
	{
		*mousestates = SDL_GetMouseState(&w->event.oldmouse.x,
				&w->event.oldmouse.y);
		i++;
	}
	*mousestates = SDL_GetMouseState(&w->event.newmouse.x,
			&w->event.newmouse.y);
}

void		mouse_motion_input(t_wolf_3d *w, Uint32 *mousestates)
{
	track_mouse(w, mousestates);
	mouse_limitation(w);
	if (w->event.oldmouse.x > w->event.newmouse.x)
		calculate_plane_dir_x(w, 0.05 * ((abs(w->event.oldmouse.x
							- w->event.newmouse.x) % 100)
					* (2 * w->fps.rotspeed)));
	if (w->event.oldmouse.x < w->event.newmouse.x)
		calculate_plane_dir_x(w, -0.05 * ((abs(w->event.oldmouse.x
							- w->event.newmouse.x) % 100)
					* (2 * w->fps.rotspeed)));
	if (w->event.oldmouse.y > w->event.newmouse.y
			&& w->event.newmouse.y < WIDTH && w->event.oldmouse.y < WIDTH)
	{
		w->event.up_mouve = (w->event.oldmouse.y - w->event.newmouse.y);
		w->event.down_mouve = (w->event.oldmouse.y - w->event.newmouse.y);
	}
	if (w->event.oldmouse.y < w->event.newmouse.y
			&& w->event.newmouse.y > 0 && w->event.oldmouse.y > 0)
	{
		w->event.up_mouve = -(w->event.newmouse.y - w->event.oldmouse.y);
		w->event.down_mouve = -(w->event.newmouse.y - w->event.oldmouse.y);
	}
	if (w->event.oldmouse.x != w->event.newmouse.x)
		w->event.oldmouse.x = w->event.newmouse.x;
}
