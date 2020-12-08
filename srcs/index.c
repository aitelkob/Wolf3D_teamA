/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:23:04 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/12/08 20:48:30 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

void index_page(t_wolf_3d *w, int *i)
{
    w->sdl.page = 0;
    if (*i <= 30)
    {
        w->sdl.index = IMG_Load(INDEX);
        w->sdl.index_tex = SDL_CreateTextureFromSurface(w->sdl.renderer,
                                                        w->sdl.index);
        SDL_RenderCopy(w->sdl.renderer, w->sdl.index_tex, NULL, NULL);
        (*i)++;
    }
}

void index_page2(t_wolf_3d *w)
{
    w->sdl.page = 2;
    w->sdl.index = IMG_Load(INDEX2);
    w->sdl.index_tex = SDL_CreateTextureFromSurface(w->sdl.renderer,
                                                    w->sdl.index);
    SDL_RenderCopy(w->sdl.renderer, w->sdl.index_tex, NULL, NULL);
}

void index_page3(t_wolf_3d *w, int *i)
{
    w->sdl.page = 3;
    w->sdl.index = IMG_Load(INDEX3);
    w->sdl.index_tex = SDL_CreateTextureFromSurface(w->sdl.renderer,
                                                    w->sdl.index);
    SDL_RenderCopy(w->sdl.renderer, w->sdl.index_tex, NULL, NULL);
    SDL_RenderPresent(w->sdl.renderer);
    (*i)++;
}

void start_index_page(t_wolf_3d *w, int *i)
{
    SDL_Rect dst;

    dst.w = 100;
    dst.h = 100;
    dst.x = (WIDTH / 2) - (dst.w / 2);
    dst.y = (HEIGHT / 2) - (dst.h / 2);
    index_page2(w);
    if (w->sdl.event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (w->sdl.event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_GetMouseState(&w->event.newmouse.x, &w->event.newmouse.y);
            if (((w->event.newmouse.x >= 344 && w->event.newmouse.y >= 638) && (w->event.newmouse.x <= 558 && w->event.newmouse.y <= 700)) && w->sdl.page == 2)
            {
                w->sdl.page = 3;
                w->sdl.index_i = 1;
            }
            else if (((w->event.newmouse.x >= 344 && w->event.newmouse.y >= 742) && (w->event.newmouse.x <= 558 && w->event.newmouse.y <= 806)) && w->sdl.page == 2)
                w->game_running = 1;
        }
    }
    if (w->sdl.index_i)
        index_page3(w, i);
}

void main_page(t_wolf_3d *w, int *i)
{
    if (w->sdl.page == 0)
    {
        if (*i <= 30)
            index_page(w, i);
        else
            w->sdl.page = 2;
    }
    else if (w->sdl.page == 2)
        start_index_page(w, i);
    else if (w->sdl.page == 3)
    {
        if (w->sdl.event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (w->sdl.event.button.button == SDL_BUTTON_LEFT)
            {
                SDL_GetMouseState(&w->event.newmouse.x, &w->event.newmouse.y);
                if (((w->event.newmouse.x >= 108 && w->event.newmouse.y >= 361) && (w->event.newmouse.x <= 287 && w->event.newmouse.y <= 542)) && w->sdl.page == 3)
                {
                    w->sdl.page = 3;
                    w->sdl.index_i_tex = 1;
                    w->sdl.new_text[0] = (unsigned int *)w->sdl.wall1->pixels;
                    w->sdl.new_text[1] = (unsigned int *)w->sdl.wall2->pixels;
                    w->sdl.new_text[2] = (unsigned int *)w->sdl.wall3->pixels;
                    w->sdl.new_text[3] = (unsigned int *)w->sdl.wall4->pixels;
                }
                else if (((w->event.newmouse.x >= 361 && w->event.newmouse.y >= 361) && (w->event.newmouse.x <= 540 && w->event.newmouse.y <= 542)) && w->sdl.page == 3)
                {
                    w->sdl.page = 3;
                    w->sdl.index_i_tex = 1;
                    w->sdl.new_text[0] = (unsigned int *)w->sdl.wall5->pixels;
                    w->sdl.new_text[1] = (unsigned int *)w->sdl.wall6->pixels;
                    w->sdl.new_text[2] = (unsigned int *)w->sdl.wall7->pixels;
                    w->sdl.new_text[3] = (unsigned int *)w->sdl.wall8->pixels;
                }
                else if (((w->event.newmouse.x >= 641 && w->event.newmouse.y >= 361) && (w->event.newmouse.x <= 792 && w->event.newmouse.y <= 542)) && w->sdl.page == 3)
                {
                    w->sdl.page = 3;
                    w->sdl.index_i_tex = 1;
                    w->sdl.new_text[0] = (unsigned int *)w->sdl.wall9->pixels;
                    w->sdl.new_text[1] = (unsigned int *)w->sdl.wall10->pixels;
                    w->sdl.new_text[2] = (unsigned int *)w->sdl.wall11->pixels;
                    w->sdl.new_text[3] = (unsigned int *)w->sdl.wall12->pixels;
                }
                else if (((w->event.newmouse.x >= 344 && w->event.newmouse.y >= 742) && (w->event.newmouse.x <= 558 && w->event.newmouse.y <= 806)) && w->sdl.page == 3)
                    w->game_running = 1;
            }
        }
        if (w->sdl.index_i_tex)
        {
            draw_map_3d(w);
            SDL_UpdateTexture(w->sdl.texture, NULL, w->data, WIDTH * sizeof(int));
            SDL_RenderCopy(w->sdl.renderer, w->sdl.texture, NULL, NULL);
            image_clear(w);
            mini_map(w);
            mini_player(w);
            load_font(w);
            SDL_RenderCopy(w->sdl.renderer, w->sdl.cur_tex, NULL, &w->dst);
        }
    }
}