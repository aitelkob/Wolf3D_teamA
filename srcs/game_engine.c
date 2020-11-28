/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 05:14:13 by yait-el-          #+#    #+#             */
/*   Updated: 2020/11/28 03:48:29 by yait-el-         ###   ########.fr       */
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

void wall_texture(t_wolf_3d *wolf, int x, int start, int end)
{
	// int i;

	// * multiple texture
	// int wallnbr = wolf->player.world_map[wolf->ray.map.x][wolf->ray.map.y];
	// printf("lnbr %d \n",wallnbr);
	if (wolf->ray.side == 1)
		wolf->wallx = wolf->player.pos.x + wolf->ray.perpWallDist * wolf->ray.raydir.x;
	else
		wolf->wallx = wolf->player.pos.y + wolf->ray.perpWallDist * wolf->ray.raydir.y;
	wolf->wallx -= floor(wolf->wallx);
	//x coordinate on the texture
	wolf->texx = (int)(wolf->wallx * (double)TEXT_W);
	if (wolf->ray.side == 0 && wolf->ray.raydir.x > 0)
		wolf->texx = TEXT_W - wolf->texx - 1;
	if (wolf->ray.side == 1 && wolf->ray.raydir.y < 0)
		wolf->texx = TEXT_W - wolf->texx - 1;
	// i = wolf->ray.draw.start;
	while (start < end)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		wolf->texy = ((start - wolf->event.down_mouve) * 2 - HEIGHT +
					  wolf->ray.lineHeight) *
					 (TEXT_H / 2) / wolf->ray.lineHeight;
		if (start < HEIGHT && start >= 0)
			wolf->data[start * WIDTH + x] = wolf->sdl.wall_data_tmp[wolf->texy * TEXT_H + wolf->texx];
		start++;
	}
}

/*
**	The problem is that you loop 2 times on x 
**	the first is here and the second time is when the fill_data_tab Fucntion
**	is called for the the draw_3d_map
**	change this function to work like this, Texture_Floor(t_wolf_3d *w, int x)
*/

void Texture_Floor(t_wolf_3d *w)
{
	int y;
	int x;

		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		w->ray.ray0.x = w->player.dir.x - w->player.plane.x;
		w->ray.ray0.y = w->player.dir.y - w->player.plane.y;
		w->ray.ray1.x = w->player.dir.x + w->player.plane.x;
		w->ray.ray1.y = w->player.dir.y + w->player.plane.y;
	y = HEIGHT / 2 + w->event.down_mouve;
	while (y < HEIGHT)
	{
		// Current y position compared to the center of the screen (the horizon)
		w->p = (y - HEIGHT / 2) - w->event.down_mouve;
		// Vertical position of the camera.
		w->posZ = 0.5 * HEIGHT;
		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		w->rowDistance = w->posZ / w->p;
		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		w->floorStepX = w->rowDistance * (w->ray.ray1.x - w->ray.ray0.x) / WIDTH;
		w->floorStepY = w->rowDistance * (w->ray.ray1.y - w->ray.ray0.y) / WIDTH;

		// real world coordinates of the leftmost column. This will be updated as we step to the right
		w->floorX = w->player.pos.x + w->rowDistance * w->ray.ray0.x;
		w->floorY = w->player.pos.y + w->rowDistance * w->ray.ray0.y;
		x = 0;
		while (x < WIDTH)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			w->cellX = (int)(w->floorX);
			w->cellY = (int)(w->floorY);
			// get the texture coordinate from the fractional part
			w->texx2 = (int)(TEXT_W * (w->floorX - w->cellX)) & (TEXT_W - 1);
			w->texy2 = (int)(TEXT_H * (w->floorY - w->cellY)) & (TEXT_H - 1);
			w->floorX += w->floorStepX;
			w->floorY += w->floorStepY;
			//floor
			if ((y ) >= 0 &&  (y) <  HEIGHT)
			w->data[WIDTH * y + x] = w->sdl.wall_data_floor[TEXT_W * w->texx2 + w->texy2] ;
			x++;
		}
		y++;
	}
}
void Texture_cling(t_wolf_3d *w)
{
    int y;
    int x;

        // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
        w->ray.ray0.x = w->player.dir.x - w->player.plane.x;
        w->ray.ray0.y = w->player.dir.y - w->player.plane.y;
        w->ray.ray1.x = w->player.dir.x + w->player.plane.x;
        w->ray.ray1.y = w->player.dir.y + w->player.plane.y;
    y = 0;
    while (y < (HEIGHT / 2))
    {
        // Current y position compared to the center of the screen (the horizon)
        w->p = -1 * ((y - HEIGHT / 2));
        // Vertical position of the camera.
        w->posZ = 0.5 * HEIGHT;
        // Horizontal distance from the camera to the floor for the current row.
        // 0.5 is the z position exactly in the middle between floor and ceiling.
        w->rowDistance = w->posZ / w->p;
        // calculate the real world step vector we have to add for each x (parallel to camera plane)
        // adding step by step avoids multiplications with a weight in the inner loop
        w->floorStepX = w->rowDistance * (w->ray.ray1.x - w->ray.ray0.x) / WIDTH;
        w->floorStepY = w->rowDistance * (w->ray.ray1.y - w->ray.ray0.y) / WIDTH;

        // real world coordinates of the leftmost column. This will be updated as we step to the right
        w->floorX = w->player.pos.x + w->rowDistance * w->ray.ray0.x;
        w->floorY = w->player.pos.y + w->rowDistance * w->ray.ray0.y;
        x = 0;
        while (x < WIDTH)
        {
            // the cell coord is simply got from the integer parts of floorX and floorY
            w->cellX = (int)(w->floorX);
            w->cellY = (int)(w->floorY);
            // get the texture coordinate from the fractional part
            w->texx2 = (int)(TEXT_W * (w->floorX - w->cellX)) % (TEXT_W - 1);
            w->texy2 = (int)(TEXT_H * (w->floorY - w->cellY)) % (TEXT_H - 1);
            w->floorX += w->floorStepX;
            w->floorY += w->floorStepY;
            //floor
			if ( y <  HEIGHT)
            w->data[WIDTH * y + x] = w->sdl.wall_data_floor[TEXT_W * w->texx2 + w->texy2] ;
            x++;
        }
        y++;
    }
}


void fill_data_tab(t_wolf_3d *w, int x)
{
	// int i;
	(void)x;
	(void)w;
	// i = 0;
	// while (i < w->ray.draw.start)
	// {
	// 	w->data[x + (i * WIDTH)] = 0x99cfe0;
	// 	i++;
	// }
	// i = w->ray.draw.end;
	// while (i < HEIGHT)
	// {
	// 	w->data[x + (i * WIDTH)] = 0x654321;
	// 	i++;
	// }
	wall_texture(w, x, w->ray.draw.start, w->ray.draw.end);
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

/*
**  calculate ray position and direction
**  length of ray from one x or y-side to next x or y-side
**  was there a wall hit?
**  coord of the square ( which box of the map we're in )
**  calculate step and initial sideDist
**  Perform DDA
**  Calculate distance projected on camera direction
*/

void draw_map_3d(t_wolf_3d *w)
{
	int x;
	double tmp1;
	double tmp2;

	x = 0;
	Texture_cling(w);
	Texture_Floor(w);
	while (x < WIDTH)
	{
		w->ray.cameraX = 2 * x / (double)WIDTH - 1;
		w->ray.raydir.x = w->player.dir.x + w->player.plane.x * w->ray.cameraX;
		w->ray.raydir.y = w->player.dir.y + w->player.plane.y * w->ray.cameraX;
		tmp1 = (w->ray.raydir.x == 0) ? 1 : fabs(1 / w->ray.raydir.x);
		tmp2 = (w->ray.raydir.y == 0) ? 1 : fabs(1 / w->ray.raydir.y);
		w->ray.deltadist.x = (w->ray.raydir.y == 0) ? 0 : tmp1;
		w->ray.deltadist.y = (w->ray.raydir.x == 0) ? 0 : tmp2;
		w->ray.hit = 0;
		w->ray.map.x = (int)w->player.pos.x;
		w->ray.map.y = (int)w->player.pos.y;
		step_taken(w);
		dda_algorithm(w);
		detect_start_end(w);
		fill_data_tab(w, x);
		x++;
	}
}
