/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 02:19:41 by yait-el-          #+#    #+#             */
/*   Updated: 2020/12/05 02:24:04 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

void update(t_wolf_3d *w)
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), (w->fps.last_frame_time + w->fps.frame_target)))
        ;
    w->fps.delta_time = (SDL_GetTicks() - w->fps.last_frame_time) / 1000.0f;
    w->fps.last_frame_time = SDL_GetTicks();
    w->fps.movespeed = 3 * w->fps.delta_time;
    w->fps.rotspeed = 2 * w->fps.delta_time;
}

void        imga_copy(t_wolf_3d *w)
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
