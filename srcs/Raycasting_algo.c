/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting_algo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 02:16:42 by yait-el-          #+#    #+#             */
/*   Updated: 2020/10/28 04:53:38 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf_3d.h"

/*
**  Creating a render (The act of drawing the modelled object on screen)
**  then
**  Creating a texture image the draw the map on
*/

void calculate_plane_dir_x(t_wolf_3d *w, double rotation_speed)
{
    float cos_calc;
    float sin_calc;

    cos_calc = cos(rotation_speed);
    sin_calc = sin(rotation_speed);
    w->oldDirX = w->player.dir.x;
    w->player.dir.x = w->player.dir.x * cos_calc - w->player.dir.y * sin_calc;
    w->player.dir.y = w->oldDirX * sin_calc + w->player.dir.y * cos_calc;
    w->oldplaneX = w->player.plane.x;
    w->player.plane.x = w->player.plane.x * cos_calc - w->player.plane.y * sin_calc;
    w->player.plane.y = w->oldplaneX * sin_calc + w->player.plane.y * cos_calc;
}

void step_taken(t_wolf_3d *w)
{
    if (w->ray.raydir.x < 0)
    {
        w->ray.step.x = -1;
        w->ray.sidedist.x = (w->player.pos.x - w->ray.map.x) * w->ray.deltadist.x;
    }
    else
    {
        w->ray.step.x = 1;
        w->ray.sidedist.x = (w->ray.map.x + 1.0 - w->player.pos.x) * w->ray.deltadist.x;
    }
    if (w->ray.raydir.y < 0)
    {
        w->ray.step.y = -1;
        w->ray.sidedist.y = (w->player.pos.y - w->ray.map.y) * w->ray.deltadist.y;
    }
    else
    {
        w->ray.step.y = 1;
        w->ray.sidedist.y = (w->ray.map.y + 1.0 - w->player.pos.y) * w->ray.deltadist.y;
    }
}

/*
**  Jump to next map square, OR in x-direction, OR in y-direction
**  Check if ray has hit a wall
*/

void dda_algorithm(t_wolf_3d *w)
{
    while (w->ray.hit == 0)
    {
        if (w->ray.sidedist.x < w->ray.sidedist.y)
        {
            w->ray.sidedist.x += w->ray.deltadist.x;
            w->ray.map.x += w->ray.step.x;
            w->ray.side = 0;
        }
        else
        {
            w->ray.sidedist.y += w->ray.deltadist.y;
            w->ray.map.y += w->ray.step.y;
            w->ray.side = 1;
        }
        if (w->player.world_map[w->ray.map.x][w->ray.map.y] > 0)
            w->ray.hit = 1;
    }
    if (w->ray.side == 0)
        w->ray.perpWallDist = (w->ray.map.x - w->player.pos.x +
                               (1 - w->ray.step.x) / 2) /
                              w->ray.raydir.x;
    else
        w->ray.perpWallDist = (w->ray.map.y - w->player.pos.y +
                               (1 - w->ray.step.y) / 2) /
                              w->ray.raydir.y;
}

/*
**  Draw sky
**  Draw flor
**  Draw a vertical line from drawStart to drawEnd
*/

void fill_data_tab(t_wolf_3d *w, int x)
{
    int i;

    i = 0;
    while (i < w->ray.draw.start)
    {
        w->data[x + (i * WIDTH)] = 0x99cfe0;
        i++;
    }
    i = w->ray.draw.end;
    while (i < HEIGHT)
    {
        w->data[x + (i * WIDTH)] = 0x654321;
        i++;
    }
    while (w->ray.draw.start <= w->ray.draw.end)
    {
        w->ray.color = 0;
        if (w->ray.side == 1)
            w->ray.color = 0xffffff;
        else
            w->ray.color = 0x808080;
        w->data[x + (w->ray.draw.start * WIDTH)] = w->ray.color;
        w->ray.draw.start++;
    }
}

/*
**  Calculate height of line to draw on screen
**  calculate lowest pixel to fill in current stripe
**  Calculate highest pixel to fill in current stripe
*/

void detect_start_end(t_wolf_3d *w)
{
    w->ray.lineHeight = (int)(HEIGHT / w->ray.perpWallDist) * 0.5;
    if (w->ray.perpWallDist <= 0)
        w->ray.lineHeight = WIDTH;
    w->ray.draw.start = (int)((-w->ray.lineHeight / 2) + (HEIGHT / 2)) + w->event.up_mouve;
    if (w->ray.draw.start < 0)
        w->ray.draw.start = 0;
    w->ray.draw.end = (int)((w->ray.lineHeight / 2) + (HEIGHT / 2)) + w->event.down_mouve;
    if (w->ray.draw.end >= HEIGHT)
        w->ray.draw.end = HEIGHT - 1;
}
