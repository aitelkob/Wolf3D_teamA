/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 06:00:53 by yait-el-          #+#    #+#             */
/*   Updated: 2020/02/25 03:24:34 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Wolf3D.h"

int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

};
int		init_win(t_mlix *mlix)
{

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("Error initializing SDL. \n");
		return (-1);	
	}
	// Create window of the application

	mlix->window = SDL_CreateWindow(
			"Wolf3D-yuss",// window title
			SDL_WINDOWPOS_CENTERED, //// initial x position IN mac Desktop
			SDL_WINDOWPOS_CENTERED, //// initial y position IN mac Desktop
			WIN_WIDTH, /// width, in pixels
			WIN_HEAIGHT, /// height, in pixels
			SDL_WINDOW_BORDERLESS
			);
	// Check that the window was successfully created
	if (!(mlix->window))
	{
		// In the case that the window could not be made...
		printf("Could not create window: %s\n",SDL_GetError());
		return (-1);
	}

	mlix->renderer = SDL_CreateRenderer(
			mlix->window,//the window where rendering is displayed
			-1, //// the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
			0 /// 0, or one or more SDL_RendererFlags OR'd together; see Remarks for details
			);
	if (!(mlix->renderer))
	{
		// In the case that the window could not be made...
		printf("Errror creating SDL Renderer  %s\n",SDL_GetError());
		return (-1);
	}
	return (1);
}

void        setup(t_mlix *mlix)
{
	mlix->player_cord.x = WIN_WIDTH/2;
	mlix->player_cord.y = WIN_HEAIGHT/2;
	mlix->player_cord.width = 1;
	mlix->player_cord.height = 1;
	mlix->player_cord.turnDirection = 0;
	mlix->player_cord.walkSpeed = 0;
	mlix->player_cord.rotationAngle = PI /2;
	mlix->player_cord.RetationSpeed = 45 * (PI / 180);
	mlix->player_cord.walkSpeed = 100;
	mlix->lastFrame = 0;
	mlix->Fps = 30;
	mlix->image = (unsigned int *)malloc(sizeof(int) * WIN_HEAIGHT * WIN_WIDTH);
	mlix->SDL_textuu = SDL_CreateTexture(
			mlix->renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			WIN_WIDTH,
			WIN_HEAIGHT
			);
}

void		image_clear(t_mlix *mlix)
{
	int x = 0;
	int y ;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEAIGHT)
		{
			mlix->image[(WIN_WIDTH * y) + x] = 0xff3a9b33;
			y++;
		}
		x++;
	}

}

int			is_wall_here(double x,double y,t_mlix *mlix)
{
	(void)mlix;

	if ( x < 0 || x > WIN_WIDTH || y < 0 || y >WIN_HEAIGHT)
		return (1);

	int new_x = floor(x / TILE_SIZE);
	int new_y = floor(y / TILE_SIZE);
	printf(" value  %d \n",map[new_y][new_x]);
	return (map[new_y][new_x] != 0 );
}

void		move_player(t_mlix *mlix)
{
	mlix->player_cord.rotationAngle += mlix->player_cord.turnDirection * mlix->player_cord.RetationSpeed *mlix->deltaTime;
	double move = mlix->player_cord.walkDirection * mlix->player_cord.walkSpeed * mlix->deltaTime;

	double newPlayerX = mlix->player_cord.x + cos(mlix->player_cord.rotationAngle) * move;
	double  newPlayerY = mlix->player_cord.y + sin(mlix->player_cord.rotationAngle) * move;
	printf("movesetp == %f  %f \n",move,mlix->deltaTime);
	if (!(is_wall_here(newPlayerX, newPlayerY,mlix)))
	{
		mlix->player_cord.x =  newPlayerX;
		mlix->player_cord.y = newPlayerY;
	}
}

void			draw_player(t_mlix	*mlix)
{
	////set the color of the player
	SDL_SetRenderDrawColor(mlix->renderer,255,255,255,255);
	///// create rect
	mlix->player_rect = (SDL_Rect){mlix->player_cord.x*MAP_SACLER,
		mlix->player_cord.y*MAP_SACLER,
		mlix->player_cord.width*MAP_SACLER,
		mlix->player_cord.height*MAP_SACLER};
	SDL_RenderFillRect(mlix->renderer,&mlix->player_rect);
	SDL_RenderDrawLine(mlix->renderer,
			mlix->player_cord.x*MAP_SACLER,
			mlix->player_cord.y*MAP_SACLER,
			MAP_SACLER*(mlix->player_cord.x  + cos(mlix->player_cord.rotationAngle) * 40),
			MAP_SACLER*(mlix->player_cord.y  + sin(mlix->player_cord.rotationAngle) * 40));
}

void			draw_map(t_mlix		*mlix)
{
	int i = 0;
	int j ;
	int x_exp = 0;
	int y_exp = 0;
	int color_map;

	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			x_exp = j * TILE_SIZE;
			y_exp = i * TILE_SIZE;
			color_map = map[i][j] != 0 ? 255 : 0;
			SDL_SetRenderDrawColor(mlix->renderer,color_map,color_map,color_map,255);
			mlix->map = (SDL_Rect){
				x_exp*MAP_SACLER,
					y_exp*MAP_SACLER,
					TILE_SIZE*MAP_SACLER,
					TILE_SIZE*MAP_SACLER};
			SDL_RenderFillRect(mlix->renderer,&mlix->map);
			j++;
		}
		i++;
	}
}

void            update(t_mlix *mlix)
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(),mlix->lastFrame+frame_time));
	mlix->deltaTime = (SDL_GetTicks() - mlix->lastFrame) / 1000.0f;
	mlix->lastFrame = SDL_GetTicks();
	move_player(mlix);
	cast_all_rays(mlix);
}

void			draw_image(t_mlix *mlix)
{
	SDL_UpdateTexture(
			mlix->SDL_textuu,
			NULL,
			mlix->image,
			WIN_WIDTH * sizeof(unsigned int)
			);
	SDL_RenderCopy(mlix->renderer,mlix->SDL_textuu,NULL,NULL);
}

void			draw(t_mlix *mlix)
{
	SDL_SetRenderDrawColor(mlix->renderer,0,0,0,255);

	//draw_image(mlix);
	// set all color to black
	//SDL_RenderClear(mlix->renderer);

	draw_map(mlix);
	draw_rays(mlix);
	draw_player(mlix);

	SDL_RenderPresent(mlix->renderer);
}

int main(int ac,char **av)
{
	(void)ac;
	(void)av;
	t_mlix mlix;
	///////////////// init SDL window///////////////
	mlix.game = init_win(&mlix);
	///////////////// set up 
	setup(&mlix);	
	////////////// game loop//////////////////
	while (mlix.game)
	{
		///process();
		event_handler(&mlix);
		update(&mlix);
		draw(&mlix);
		//player_update(&mlix);
	}
	return (0);
}
