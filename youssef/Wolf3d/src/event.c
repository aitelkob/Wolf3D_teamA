/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 02:21:35 by yait-el-          #+#    #+#             */
/*   Updated: 2020/03/05 19:04:11 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Wolf3D.h"

void        event_handler(t_mlix *mlix)
{
	SDL_Event          event;

	SDL_PollEvent(&event);


	if (event.type == SDL_QUIT)
		mlix->game = 0;
	 if (event.type == SDL_KEYDOWN)
	{
		if(event.key.keysym.sym == SDLK_ESCAPE)
			mlix->game = 0;
		if (event.key.keysym.sym == SDLK_UP)
			mlix->player_cord.walkDirection = +1;
		if (event.key.keysym.sym == SDLK_DOWN)
			mlix->player_cord.walkDirection=  -1;
		if (event.key.keysym.sym == SDLK_LEFT)
			mlix->player_cord.turnDirection=  -1;
		if (event.key.keysym.sym == SDLK_RIGHT)
			mlix->player_cord.turnDirection=  +1;
		return;
	}
	 if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP)
			mlix->player_cord.walkDirection =0;
		if (event.key.keysym.sym == SDLK_DOWN)
			mlix->player_cord.walkDirection =0;
		if (event.key.keysym.sym == SDLK_LEFT)
			mlix->player_cord.turnDirection =0;
		if (event.key.keysym.sym == SDLK_RIGHT)
			mlix->player_cord.turnDirection =0;
		return;
	}

}
