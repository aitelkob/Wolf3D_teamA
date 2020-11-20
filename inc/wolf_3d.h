/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:21:28 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/11/20 02:01:22 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_3D_H
# define WOLF_3D_H

# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# define TEXT_CEILING "./img/021-brickgreybrownmould1.bmp"
# define GRAYSTONE "./pics/greystone.png"
# define PURPLESTONE "./pics/purplestone.png"
# define REDBRICK "./pics/redbrick.png"
# define WOOD "./pics/wood.png"
# define MOSSY "./pics/mossy.png"
# define COLORSTONE "./pics/colorstone.png"
# define BLUESTONE "./pics/bluestone.png"
# include "../SDL/SDL2.framework/Headers/SDL.h"
# include "../SDL/SDL2_image.framework/Headers/SDL_image.h"

# define WIDTH 800
# define HEIGHT 800
# define TEXT_W 64
# define TEXT_H 64
# define mapWidth 24
# define mapHeight 24
# define PNG "/img/Png.png"
// # define FPS 60
# define TRUE 1
# define FALSE 0
// # define FRAME_TARGET_TIME (1000 / FPS)

# define  MAP_NUM_ROWS  24
# define  MAP_NUM_COLS  24
# define  TILE_SIZE  64
# define  MAP_SACLER  0.4

typedef struct			s_point
{
	double				x;
	double				y;
}						t_point;

typedef struct			s_coord
{
	int					x;
	int					y;
}						t_coord;

typedef struct			s_walls
{
	int					start;
	int					end;
}						t_walls;

typedef struct			t_fps
{
	float				delta_time;
	int					last_frame_time;
	double				frame_target;
	int					fps;
	double				movespeed;
	double				rotspeed;
}						t_fps;

// typedef struct			s_texture
// {
// 	SDL_Surface			*texture_surf;
// 	SDL_Texture			*texture;
// 	int					*tmp;
// 	int					w;
// 	int					h;
// }						t_texture;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Event			event;
	SDL_Surface			*cur;
	SDL_Texture			*cur_tex;
	SDL_Surface			*wall_wood;
	SDL_Surface         *ceiling_texture;
	SDL_Surface         *roof_texture;
	SDL_Surface         *floor_texture;
	unsigned int		*wall_data_wood;
	SDL_Surface			*txt_fps;
	SDL_Rect			map;
	SDL_Rect 			player;
}						t_sdl;

typedef struct			s_player
{
	t_point				pos;
	t_point				dir;
	t_point				plane;
	int					with;
	int					height;
	int					**world_map;
}						t_player;

typedef struct			s_event
{
	t_coord				newmouse;
	t_coord				oldmouse;
	int					up_mouve;
	int					down_mouve;
}						t_event;

typedef	struct			s_ray
{
    int         		color;
	double      		cameraX;
	double				perpWallDist;
	int					hit;
	int					side;
	int					lineHeight;
	t_point				raydir;
	t_point				sidedist;
	t_point				deltadist;
	t_coord				step;
	t_coord				map;
	t_walls				draw;
}						t_ray;

typedef struct			s_wolf_3d
{
	int					game_running;
	t_sdl				sdl;
	t_player			player;
	t_ray				ray;
	t_event				event;
	t_fps				fps;
	Uint32				mousestates;
	t_coord				texture[8]; 
	SDL_Texture 		*texturei;
 	SDL_Surface			*wall_texture;
	SDL_Rect			dst;
	unsigned int        *wall_image;
	int					texture_index;
	double				wallx;
	int					texx;
	int					texy;
    int					*data;
	double				oldDirX;
	double				oldplaneX;
}						t_wolf_3d;
/*
 *
 *
*/
/*
	**	Outils
*/
void					clear_data_tab(int    *tab);

int						sdl_init_texture(t_wolf_3d	*w);
int         			sdl_init_render(t_wolf_3d   *w);
int						sdl_init_win(t_wolf_3d	*w);
void					sdl_text_init(t_wolf_3d *w);

/*
	**	Main
*/
void					load_img(t_wolf_3d *w, const char *file);
void					draw_cube(t_wolf_3d *w, int x_begin, int y_begin, int color);
void					draw_map(t_wolf_3d *w);
void					draw_map_3d(t_wolf_3d *w);
void					game_engine(t_wolf_3d *w);
void					calculate_plane_dir_x(t_wolf_3d *w, double rotation_speed);
void					mouse_motion_input(t_wolf_3d *w, Uint32	*mousestates);
void					step_taken(t_wolf_3d *w);
void					key_down_input(t_wolf_3d *w, const Uint8 *keystates, int	**world_map);
void					process_input(t_wolf_3d *w, int	**world_map);
void					mouse_limitation(t_wolf_3d *w);
void					fill_data_tab(t_wolf_3d *w, int x);
void					detect_start_end(t_wolf_3d *w);
void					dda_algorithm(t_wolf_3d *w);
int         			**get_map(int **map, int fd, char    **av);
void        mini_map(t_wolf_3d *w);
void        image_clear(t_wolf_3d *wolf);
void		player_inMini(t_wolf_3d *w);
void        loadTexture(t_wolf_3d *wolf);
void        texture_img(t_wolf_3d *wolf);
void					process_input(t_wolf_3d *w, int	**world_map);
void					init_perso(t_wolf_3d *w);
void					show_error1();
void					how_error2(char *str);
void					show_error3();
#endif
