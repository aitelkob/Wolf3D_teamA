# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/25 10:38:14 by ayagoumi          #+#    #+#              #
#    Updated: 2020/11/25 23:59:17 by yait-el-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Executable / Libraries.

RM              = rm -rf
SDL             = libsdl2.a
TTF             = libsdl2_ttf.a
IMG				= libSDL2_image.a
FT              = libft.a
LFTDIR			= libft
NAME            = Wolf 
###########################color code 
BLACK        	:= $(shell tput -Txterm setaf 0)
RED          	:= $(shell tput -Txterm setaf 1)
GREEN        	:= $(shell tput -Txterm setaf 2)
YELLOW       	:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE  	:= $(shell tput -Txterm setaf 4)
PURPLE       	:= $(shell tput -Txterm setaf 5)
BLUE         	:= $(shell tput -Txterm setaf 6)
WHITE        	:= $(shell tput -Txterm setaf 7)
RESET         	= \033[0m
############################
INCSDIR 		:= inc
INCSDIR 		+= $(LFTDIR)
############################
SRCSDIR 		= srcs
OBJSDIR 		= objs
############################
INCS 			:= inc/wolf_3d.h
INCS 			+= libft/libft.h
############################################
SRC 			:= main.c
SRC 			+= stock_map.c
SRC 			+= texture.c
SRC 			+= events.c
SRC 			+= wolf_miniMap.c
SRC 			+= init_wolf.c
SRC 			+= game_engine.c
SRC 			+= outils.c
SRC 			+= sdl_init.c
#############################################
LSDLDIR     = $(HOME)/.brew/Cellar/sdl2/2.0.12_1/lib
LTTFDIR     = $(HOME)/.brew/Cellar/sdl2_ttf/2.0.15/lib
LIMGDIR 	= $(HOME)/.brew/Cellar/sdl2_image/2.0.5/lib
INCSDIR     += $(HOME)/.brew/Cellar/sdl2/2.0.12_1/include/SDL2
INCSDIR     += $(HOME)/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2
INCSDIR		+= $(HOME)/.brew/Cellar/sdl2_image/2.0.5/include/SDL2
########################################3Linked libraries at compile time.
LIBS            := -framework SDL2 -F ./SDL/ 
LIBS            += -framework SDL2_image -F ./SDL/
LIBS            += -framework SDL2_ttf -F ./SDL
LIBS			+= -rpath @loader_path/SDL
LIBS            += -L$(LFTDIR) -lft
LIBS            += -lm
LIBS			+= -lz
LTTF             = $(LTTFDIR)/$(TTF)
LFT              = $(LFTDIR)/$(FT)
LSDL             = $(LSDLDIR)/$(SDL)
LTTF             = $(LTTFDIR)/$(TTF)
LIMG			 = $(LIMGDIR)/$(IMG)
D_SRCS           = $(addsuffix /, $(SRCSDIR))
D_OBJS           = $(addsuffix /, $(OBJSDIR))
C_OBJS           = $(addprefix $(D_OBJS),  $(SRC:.c=.o))
C_INCS           = $(foreach include, $(INCSDIR), -I$(include))

CC              = gcc

# Compilation flags.

CFLAGS          = $(C_INCS) -Wall -Wextra -Werror
#----------------->>>>>>>>>>>>>>>>START<<<<<<<<<<<<<-------------------#
$(D_OBJS)%.o: $(D_SRCS)%.c $(INCS)
	@echo "$(YELLOW)**********>>>Compiling : $(RESET) $(LIGHTPURPLE)" $<
	@$(CC) $(CFLAGS) -c $< -o $@ 


all:$(OBJSDIR) $(C_OBJS) $(NAME)


$(NAME): $(LFT)  $(LSDL) $(LIMG) $(LTTF)  $(C_OBJS)
	@echo "$(YELLOW)\n**********>>>Building : $(RESET)$(NAME) $(YELLOW)...\n$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(C_OBJS) $(LIBS)
	@echo "$(GREEN)***   successfully compiled   ***\n$(RESET)"

print-%  : ; @echo $* = $($*)

####  make libft

$(LFT):
	@make -sC $(LFTDIR)

### creating files for object.o

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

# Deleting all .o files.

clean:
	@make -sC $(LFTDIR) clean
	@echo "$(GREEN)**********   Deleting all object from $(NAME) **********\n$(RESET)"
	@$(RM) $(C_OBJS)

fclean: clean
	@make -sC $(LFTDIR) fclean
	@echo "$(GREEN)**********   Deleting $(NAME) **********\n$(RESET)"
	@$(RM) $(NAME)
	@$(RM) $(OBJSDIR)

re: fclean all
.PHONY: all clean fclean re
