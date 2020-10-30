/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 06:00:53 by yait-el-          #+#    #+#             */
/*   Updated: 2020/10/29 23:10:26 by yait-el-         ###   ########.fr       */
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
	mlix->player_cord.walkDirection = 0;
	mlix->player_cord.turnDirection = 0;
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

	/*SDL_Surface  *surface = IMG_Load("../pics/redbrick.png"); 
	SDL_Texture  *texture = SDL_CreateTextureFromSurface(renderer, surface); */
	mlix->wall_image = (unsigned int*)malloc(sizeof(int) * (int)(TEXTURE_WIDTH * TEXTURE_HEIGHT));
	mlix->png = IMG_Load("src/wood.png");
	mlix->wall_image = (unsigned int*)mlix->png->pixels;

	/*mlix->pngTexture = upng_new_from_file("src/image.jpg");
	if (mlix->pngTexture != NULL)
	{
		upng_decode(mlix->pngTexture);
		if (upng_get_error(mlix->pngTexture) == UPNG_EOK)
			mlix->wall_image = (unsigned int *) upng_get_buffer(mlix->pngTexture);
	}*/
	/*int x = 0;
	while (x < TEXTURE_HEIGHT)
	{
		int y = 0;
		while (y < TEXTURE_WIDTH)
		{
			mlix->wall_image[TEXTURE_WIDTH * y + x] = (x % 8 && y % 8)? 0xFF0000FF : 0xFF000000;
			y++;
		}
		x++;
	}*/
}
void		draw_3D(t_mlix *mlix)
{
	int i = 0;
	double dist_plan;
	double correct_fishboll;
	double projectedheight_wall;
	int		wall_rectheight,wall_top,wall_buttom;
	int		y = 0;

	while (i < num_rays)
	{
		correct_fishboll = mlix->ray[i].dist * cos(mlix->ray[i].angle - mlix->player_cord.rotationAngle);
		dist_plan  = (WIN_WIDTH /2) / tan(FOV_angle / 2);
		projectedheight_wall = (TILE_SIZE / correct_fishboll) * dist_plan;
		wall_rectheight = (int)projectedheight_wall;
		wall_top = (WIN_HEAIGHT/2) - (wall_rectheight / 2);
		wall_top = wall_top < 0 ? 0 : wall_top;
		wall_buttom = (WIN_HEAIGHT / 2) + (wall_rectheight / 2);
		wall_buttom  = wall_buttom > WIN_HEAIGHT ? WIN_HEAIGHT : wall_buttom;
		y = 0;
		while (y < wall_top)
		{
			mlix->image[(WIN_WIDTH * y) + i] = 0xFF333333;
			y++;
		}
	    y = wall_top;
		int		offsetx;
		if (mlix->ray[i].hit)
			offsetx = (int)mlix->ray[i].wall_y % TEXTURE_HEIGHT;
		else
			offsetx = (int)mlix->ray[i].wall_x % TEXTURE_WIDTH;

		while (y < wall_buttom)
		{
			int dist_top = y + (wall_rectheight /2) - (WIN_HEAIGHT /2);
			int offsety = dist_top * ((double) TEXTURE_WIDTH / wall_rectheight);
			unsigned int color_texture = mlix->wall_image[(TEXTURE_WIDTH * offsety) + offsetx];
			mlix->image[(WIN_WIDTH * y) + i] = color_texture;
			y++;
		}

		y = wall_buttom;
		int		offsety;
		if (mlix->ray[i].hit)
			    offsety = (int)mlix->ray[i].wall_y % TEXTURE_HEIGHT;
		else
			    offsety = (int)mlix->ray[i].wall_x % TEXTURE_WIDTH;

		while (y < WIN_HEAIGHT)
		{
			mlix->image[(WIN_WIDTH * y) + i] = 0xFF888888;
			y++;
		}
		i++;

	}
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
			mlix->image[(WIN_WIDTH * y) + x] = 0;
			y++;
		}
		x++;
	}

}

int			is_wall_here(double x,double y,t_mlix *mlix)
{
	(void)mlix;
	if ( x < 0 || x > WIN_WIDTH || y < 0 || y >WIN_HEAIGHT )
		return (1);

	int new_x = floor(x / TILE_SIZE);
	int new_y = floor(y / TILE_SIZE);
	return (map[new_y][new_x] != 0);
}

void		move_player(t_mlix *mlix)
{
	mlix->player_cord.rotationAngle += mlix->player_cord.turnDirection * mlix->player_cord.RetationSpeed * (mlix->deltaTime);
	float move = mlix->player_cord.walkDirection*mlix->player_cord.walkSpeed *(mlix->deltaTime);

	float  newPlayerX = mlix->player_cord.x + cos(mlix->player_cord.rotationAngle) * move;
	float newPlayerY = mlix->player_cord.y + sin(mlix->player_cord.rotationAngle) * move;

	if (!(is_wall_here(newPlayerX, newPlayerY,mlix)))
	{
		mlix->player_cord.x = newPlayerX;
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
	SDL_RenderDrawLine(mlix->renderer,mlix->player_cord.x*MAP_SACLER,mlix->player_cord.y*MAP_SACLER,MAP_SACLER*(mlix->player_cord.x  + cos(mlix->player_cord.rotationAngle) * 40),MAP_SACLER*(mlix->player_cord.y  + sin(mlix->player_cord.rotationAngle) * 40));
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
			mlix->map = (SDL_Rect){x_exp*MAP_SACLER,y_exp*MAP_SACLER,TILE_SIZE*MAP_SACLER,TILE_SIZE*MAP_SACLER};
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
	SDL_UpdateTexture(mlix->SDL_textuu,NULL,mlix->image,WIN_WIDTH * sizeof(unsigned int));
	SDL_RenderCopy(mlix->renderer,mlix->SDL_textuu,NULL,NULL);
}

void			draw(t_mlix *mlix)
{
	SDL_SetRenderDrawColor(mlix->renderer,0,0,0,255);
	SDL_RenderClear(mlix->renderer);
	draw_3D(mlix);
	draw_image(mlix);
	///set all color to black
	image_clear(mlix);
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
		event_handler(&mlix);
		update(&mlix);
		draw(&mlix);
	}
	return (0);
}
