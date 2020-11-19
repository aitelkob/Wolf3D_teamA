/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:47:25 by ayagoumi          #+#    #+#             */
/*   Updated: 2020/11/19 03:12:59 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/wolf_3d.h"

/*SDL_Surface *loadMedia(char *path)
{
  SDL_Surface  *img;
  SDL_Surface  *tmp;

  tmp = IMG_Load(path);
  if (tmp == NULL)
    exit(1);
  img = tmp;

  SDL_FreeSurface(tmp);
  return (img);
}*/

void        loadTexture(t_wolf_3d *w)
{
	w->sdl.cur = IMG_Load(PNG);
	w->sdl.wall_wood = IMG_Load(WOOD);
	w->sdl.ceiling_texture = IMG_Load(REDBRICK);
	w->sdl.roof_texture = IMG_Load(PURPLESTONE);
	w->sdl.floor_texture = IMG_Load(COLORSTONE);
	w->sdl.wall_data_wood =( int *) w->sdl.roof_texture->pixels;

	int i= 0;
	while (i < TEXT_W)
	{
		printf(" %d  " ,w->sdl.wall_data_wood[i] * -1);
		i++;
	}
	/*int i = 0;
	while (i < TEXT_W)
	{
		printf("i= %d < TEXT_W = %d \n",i,TEXT_W);
		int y = 0;
		while (y < TEXT_H)
		{
			unsigned int color_texture = w->sdl.wall_data_wood[(TEXT_W * y ) + i];
			w->data[(TEXT_W * y ) + i] = color_texture;
			y++;
		}
		i++;
	}*/
	w->sdl.cur_tex = SDL_CreateTextureFromSurface(w->sdl.renderer, w->sdl.cur);
}

void		texture_img(t_wolf_3d *w)
{
	loadTexture(w);
	SDL_UpdateTexture(w->sdl.texture, NULL, w->data, WIDTH * sizeof(int));
	SDL_RenderCopy(w->sdl.renderer, w->sdl.texture, NULL, NULL);
}
