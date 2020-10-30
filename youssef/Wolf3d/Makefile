# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 02:58:50 by yait-el-          #+#    #+#              #
#    Updated: 2020/03/09 01:24:45 by yait-el-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Wolf3D
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIB = mlx/libmlx.a \
	  libft/libft.a 
NC = -I SDL/SDL2.framework/Headers   
INC = inc/Wolf3D.h libft/libft.h 
SRC = src/main.c src/event.c src/rays.c 

FLAGCL = -lmlx -framework OpenGL -framework AppKit -framework OpenCL  -framework SDL2 -F ./SDL/ -framework SDL2_mixer -F ./SDL  -framework SDL2_image -F ./SDL -rpath @loader_path/SDL MLX/libmlx.a -lz 
OBJ = $(SRC:.c=.o) 

all: $(NAME) 
$(NAME):$(OBJ)$(INC)
		@echo "\033[95m**********make libft and minilibx_macos [OK]"
	    @Make -C ./mlx
		@make -C ./libft
		@echo "\033[92m**********done!\033[0m [OK]"
		@$(CC)  $(OBJ) $(LIB) $(FLAGCL)  $(NC) -o $(NAME)
clean:
		@echo "\033[94mcleaning..."
		@Make clean -C ./mlx
		@Make clean -C ./libft
		@rm -rf $(OBJ) 
		@echo "\033[91m**********object files removed!\033[0m [OK]"
		@echo "\033[91mdone!\033[0m"
fclean: clean 
		@rm -f $(NAME)
		@echo "\033[93m**********fdf executable removed!\033[0m [OK]"
		@Make fclean -C ./libft
		@Make fclean -C ./mlx
		@echo "\033[92m**********executable removed!\033[0m [OK]"
		
re: fclean all
norme:
		@echo "\033[96m**********norminette..."
		norminette $(SRC)
		norminette $(INC)
