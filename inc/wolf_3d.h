/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:21:28 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/12/06 20:18:23 by ayagoumi         ###   ########.fr       */
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
# define LAZZY "./fonts/lazy.ttf"
# define PNG "./pics/2.png"

# define MOLDYSTONE "./pics/moldystone.png"
# define MOLDSTONE "./pics/moldstone.png"
# define BLUECEILING "./pics/blueceiling.png"
# define BLUEFLOOR "./pics/bluefloor.png"
# define HITLERGREYSTONE "./pics/hitler_greystone.png"
# define WOOD "./pics/wood.png"

# define GREYBRICK "./pics/greybrick.png"
# define GREYSTONE "./pics/greystone.png"
# define GOLD_CUP "./pics/gold_cup.png"
# define FLAG "./pics/flag.png"

#define BLUEDEVIL "./pics/bluedevil.png"
#define CAGEWALL "./pics/cagewall.png"
#define BLUESTONE "./pics/bluestone.png"
#define BLUELINE "./pics/blueline.png"

# define BLUELINE "./pics/blueline.png"
# define REDBRICK "./pics/redbrick.png"
# define PURPLESTONE "./pics/purplestone.png"
# define COLORSTONE "./pics/colorstone.png"
# define EAGLE "./pics/eagle.png"
# define CUP "./pics/cup.png"

# include "../SDL/SDL2.framework/Headers/SDL.h"
# include "../SDL/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../SDL/SDL2_image.framework/Headers/SDL_image.h"

# define WIDTH 900
# define HEIGHT 900
# define TEXT_W 64
# define TEXT_H 64
# define mapWidth 24
# define mapHeight 24
# define  MAP_NUM_ROWS  24
# define  MAP_NUM_COLS  24
# define  TILE_SIZE  64
# define  MAP_SACLER  0.15

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
	// int					fps;
	double				movespeed;
	double				rotspeed;
}						t_fps;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Color			color;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Event			event;
	SDL_Surface			*cur;
	TTF_Font			*font;
	SDL_Texture			*msg;
	SDL_Rect			*rect_msg;
	SDL_Texture			*cur_tex;
	SDL_Surface			*Font;
	SDL_Surface			*wall;
	SDL_Surface         *wall1;
	SDL_Surface         *wall2;
	SDL_Surface         *wall3;
	SDL_Surface         *wall4;
	SDL_Surface         *wall5;
	SDL_Surface         *wall6;
	SDL_Surface         *wall7;
	SDL_Surface         *wall8;
	unsigned int		**new_text;
	int					*wall_h;
	SDL_Surface         *ceiling_texture;
	SDL_Surface         *roof_texture1;
	SDL_Surface         *floor_texture1;
	SDL_Surface         *roof_texture2;
	SDL_Surface         *floor_texture2;
	// unsigned int        *wall_data1;
	// unsigned int        *wall_data2;
	// unsigned int        *wall_data3;
	// unsigned int        *wall_data4;
	unsigned int        *wall_data_tmp;
	unsigned int		*wall_data_floor;
	unsigned int		*wall_data_ceiling;
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
	const Uint8			*keystates;
	int					light1;
	int					light2;
	double					darken_value;
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
	t_point				ray0;
	t_point				ray1;
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
	SDL_Rect			dst;
	int					wallnbr;
	int					texture_index;
	double				wallx;
	int					texx2;
	int					texy2;
    int					*data;
	double				oldDirX;
	double				oldplaneX;
	////////// flor texture
	int					p;
	double				posZ;
	double				rowDistance;
	double				floorStepX;
	double				floorStepY;
	double				floorX;
	double				floorY;
	int					cellX;
	int					cellY;
	int					texx;
	int					texy;
}						t_wolf_3d;
/*
	**	Outils
*/
void	clear_data_tab(int    *tab);
int		sdl_init_texture(t_wolf_3d	*w);
int		sdl_init_render(t_wolf_3d   *w);
int		sdl_init_win(t_wolf_3d	*w);
void	sdl_text_init(t_wolf_3d *w);
void	font_fps(t_wolf_3d *w);
void	free_surface(t_wolf_3d *w);
void	load_img(t_wolf_3d *w, const char *file);
void	draw_cube(t_wolf_3d *w, int x_begin, int y_begin, int color);
void	draw_map(t_wolf_3d *w);
void	draw_map_3d(t_wolf_3d *w);
void	game_engine(t_wolf_3d *w);
void	calculate_plane_dir_x(t_wolf_3d *w, double rotation_speed);
void	mouse_motion_input(t_wolf_3d *w, Uint32	*mousestates);
void	step_taken(t_wolf_3d *w);
void	key_down_input(t_wolf_3d *w, const Uint8 *keystates, int	**world_map);
void	process_input(t_wolf_3d *w, int	**world_map);
void	mouse_limitation(t_wolf_3d *w);
void	fill_data_tab(t_wolf_3d *w, int x);
void	detect_start_end(t_wolf_3d *w);
void	dda_algorithm(t_wolf_3d *w);
int		**get_map(int **map, int fd, char    **av);
void	mini_map(t_wolf_3d *w);
void	image_clear(t_wolf_3d *wolf);
void	player_inMini(t_wolf_3d *w);
void	loadTexture(t_wolf_3d *wolf);
void	process_input(t_wolf_3d *w, int	**world_map);
void	init_perso(t_wolf_3d *w);
void	show_error1();
void	how_error2(char *str);
void	show_error3();
void	show_error1();
void	sdl_quit(t_wolf_3d *w);
void	drawCube(t_wolf_3d *w, int x_begin, int y_begin, double scaler, int color);
void	drawMap(t_wolf_3d *w);
void	mini_player(t_wolf_3d *w);
void	free_map(char **map, int n);
void	free_map2(int **map, int n);
void	render(t_wolf_3d *w);
void	update(t_wolf_3d *w);
int 	line_numb(char *argv);
int 	ft_strlen_2_dim(char **tab);
size_t 	check(int n, int i);
int 	*values(char **tab, size_t len);
void	darken_wall_color(t_wolf_3d *w, int *color);
void	darken_fall_color(t_wolf_3d *w, int *color);
void	wall_light_input(t_wolf_3d *w, int *color);
void	light_input(t_wolf_3d *w, int *color);
void	load_font(t_wolf_3d *w);
void tex_input(t_wolf_3d *w);
#endif
