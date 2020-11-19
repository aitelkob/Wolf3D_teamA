/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 10:55:19 by yait-el-          #+#    #+#             */
/*   Updated: 2020/02/25 10:55:22 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/Wolf3D.h"

int mapo[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

};

double			normalizeAngle(double	angle)
{	
	angle = remainder(angle,PI_TOW);

	if (angle < 0)
		angle = PI_TOW + angle;
	return (angle);
}
double					dist_pointes(double x1,double y1,double x2,double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
void			cast_ray(double	rayAngle,int stripId,t_mlix *mlix)
{
	rayAngle = normalizeAngle(rayAngle);
	int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
	int isRayFacingUp = !isRayFacingDown;

	int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
	int isRayFacingLeft = !isRayFacingRight;

	double xintercept, yintercept;
	double xstep, ystep;

	int foundHorzWallHit = FALSE;
	double horzWallHitX = 0;
	double horzWallHitY = 0;
	int horzWallContent = 0;

	yintercept = floor(mlix->player_cord.y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = mlix->player_cord.x + (yintercept - mlix->player_cord.y) / tan(rayAngle);
	//
	// Calculate the increment xstep and ystep
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	double  nextHorzTouchX = xintercept;
	double  nextHorzTouchY = yintercept;
	// Increment xstep and ystep until we find a wall
	while (nextHorzTouchX >= 0 && nextHorzTouchX <= WIN_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WIN_HEAIGHT) 
	{
		double xToCheck = nextHorzTouchX;
		double yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
		if (is_wall_here(xToCheck, yToCheck,mlix)) 
		{
			// found a wall hit
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = mapo[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundHorzWallHit = 1;
			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}
	int foundVertWallHit = 0;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;
	xintercept = floor(mlix->player_cord.x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight ? TILE_SIZE : 0;
	yintercept = mlix->player_cord.y + (xintercept - mlix->player_cord.x) * tan(rayAngle);
	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;
	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;
	double nextVertTouchX = xintercept;
	double nextVertTouchY = yintercept;
	while (nextVertTouchX >= 0 && nextVertTouchX <= WIN_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WIN_HEAIGHT) {
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;
		if (is_wall_here(xToCheck, yToCheck,mlix))
		{
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = mapo[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundVertWallHit = 1;
			break;
		}
		else 
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}
	double horzHitDistance = foundHorzWallHit
		? dist_pointes(mlix->player_cord.x, mlix->player_cord.y, horzWallHitX, horzWallHitY)
		: INT_MAX;
	double vertHitDistance = foundVertWallHit
		? dist_pointes(mlix->player_cord.x, mlix->player_cord.y, vertWallHitX, vertWallHitY)
		: INT_MAX;

	if (vertHitDistance < horzHitDistance) {
		mlix->ray[stripId].dist = vertHitDistance;
		mlix->ray[stripId].wall_x = vertWallHitX;
		mlix->ray[stripId].wall_y = vertWallHitY;
		mlix->ray[stripId].content_hit = vertWallContent;
		mlix->ray[stripId].hit = 1;

	} else {
		mlix->ray[stripId].dist = horzHitDistance;
		mlix->ray[stripId].wall_x = horzWallHitX;
		mlix->ray[stripId].wall_y = horzWallHitY;
		mlix->ray[stripId].content_hit = horzWallContent;
		mlix->ray[stripId].hit = 0;

	}
	mlix->ray[stripId].angle = rayAngle;
	mlix->ray[stripId].down = isRayFacingDown;
	mlix->ray[stripId].up = isRayFacingUp;
	mlix->ray[stripId].left = isRayFacingLeft;
	mlix->ray[stripId].right = isRayFacingRight;

}

void			cast_all_rays(t_mlix *mlix)
{
	////// the first ray subtracting half of our FOV
	int			ray_id = 0;
	double		ray_angle = mlix->player_cord.rotationAngle - (FOV_angle / 2);

	while  (ray_id < num_rays)
	{
		cast_ray(ray_angle,ray_id,mlix);
		ray_angle +=FOV_angle / num_rays;
		ray_id++;
	}
}

void			draw_rays(t_mlix *mlix)
{
	int		i = 0;
	SDL_SetRenderDrawColor(mlix->renderer,255,0,0,255);

	while (i < num_rays)
	{
		SDL_RenderDrawLine(mlix->renderer,
				mlix->player_cord.x * MAP_SACLER,
				mlix->player_cord.y * MAP_SACLER,
				mlix->ray[i].wall_x * MAP_SACLER,
				mlix->ray[i].wall_y * MAP_SACLER);
		i++;
	}
}
