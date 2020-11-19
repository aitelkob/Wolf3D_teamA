/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wolf3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 04:29:01 by yait-el-          #+#    #+#             */
/*   Updated: 2020/11/06 02:51:36 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <math.h>
# include "../SDL/SDL2.framework/Headers/SDL.h"
# include "../SDL/SDL2_image.framework/Headers/SDL_image.h"
//# include "../SDL/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include <sys/sysctl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <assert.h>
# include <OpenCL/opencl.h>
# define  TILE_SIZE  64
# define  MAP_NUM_ROWS  13
# define  MAP_NUM_COLS  20
# define  TEXTURE_WIDTH 64
# define  TEXTURE_HEIGHT 64
# define  WIN_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define  WIN_HEAIGHT (MAP_NUM_ROWS * TILE_SIZE)
# define  MAP_SACLER  0.3
# define  PI  3.14159265
# define  PI_TOW 6.28318530
# define  FOV_angle (60 * (PI /180))
# define  num_rays WIN_WIDTH 
#define   frame_time  (1000/30)

typedef	struct			s_player
{
	double					x;
	double					y;
	int					wall_x;
	int					wall_y;
	double				width;
	double				height;
	int					turnDirection; // -1 for left, +1 for right
	int					walkDirection; // -1 for back, +1 for front
	double				rotationAngle;
	double				walkSpeed;
	double				RetationSpeed;
}						t_player;

typedef struct			s_ray
{
	double				angle;
	double				wall_x;
	double				wall_y;
	double				dist;
	int					hit;
	int					up;
	int					down;
	int					left;
	int					right;
	int					content_hit;
}						t_ray;

typedef	struct			s_mlix
{
	void				*ptr;
	void				*win;
	void				*imgptr;
	int                 bits_per_pixel;
	int					*img;
	int                 size_line;
	int					endian;
	double				k;
	t_player			player;
	//////The window we'll be rendering to
	SDL_Window			*window;
	t_ray				ray[num_rays];
	SDL_Renderer		*renderer;
	int 				game;
	int					**maps_value;
	SDL_Event			event;
	SDL_Rect			map;
	SDL_Rect			player_rect;
	t_player			player_cord;
	SDL_Texture			*SDL_textuu;
	SDL_Surface			*png;
	SDL_Surface         *png2;
	unsigned int		*image;
	unsigned int		*wall_image;
	double	 			deltaTime;
	double					lastFrame;
	int					Fps;

}						t_mlix;
void					draw(t_mlix *mlix);
void					event_handler(t_mlix *mlix);
void					draw_rays(t_mlix *mlix);
void					cast_ray(double ray_angle,int ray_id,t_mlix *mlix);
void					update(t_mlix *mlix);
void            cast_all_rays(t_mlix *mlix);
int         is_wall_here(double x,double y,t_mlix *mlix);
#endif
