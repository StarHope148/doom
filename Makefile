# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thparlos <thparlos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/02 11:22:48 by jcanteau          #+#    #+#              #
#    Updated: 2020/08/01 20:15:03 by thparlos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom

INC_NAME += doom.h
INC_NAME += colors.h
INC_NAME += defines.h

SRC_NAME += main.c
SRC_NAME += doom.c
SRC_NAME += sdl_start_up.c
SRC_NAME += editor_sdl.c
SRC_NAME += editor_sdl_norme.c
SRC_NAME += editor_map.c
SRC_NAME += key_hook.c
SRC_NAME += image.c
SRC_NAME += init.c
SRC_NAME += init_map.c
SRC_NAME += key_binding_pressed.c
SRC_NAME += key_binding_released.c
SRC_NAME += map_checker.c
SRC_NAME += raycaster.c
SRC_NAME += raycaster_tools.c
SRC_NAME += sampling.c
SRC_NAME += minimap.c
SRC_NAME += switch_textures.c
SRC_NAME += freeing.c
SRC_NAME += open_door.c
SRC_NAME += ray.c
SRC_NAME += save_in_file.c
SRC_NAME += xpm.c
SRC_NAME += xpm2.c
SRC_NAME += init_pthread.c
SRC_NAME += fps_text_time.c
SRC_NAME += crosshair.c
SRC_NAME += fmod_start_up.c
SRC_NAME += object_sprites.c
SRC_NAME += button.c
SRC_NAME += init_objects.c
SRC_NAME += init_object_type.c
SRC_NAME += load_textures.c
SRC_NAME += object_sprites_tools.c
SRC_NAME += projectile.c
SRC_NAME += hit.c
SRC_NAME += exit.c
SRC_NAME += items.c
SRC_NAME += player.c
SRC_NAME += gun.c
SRC_NAME += refresh_pos.c
SRC_NAME += hp_and_carried_key.c
SRC_NAME += init_object_type2.c
SRC_NAME += settings_controls.c
SRC_NAME += update_position.c
SRC_NAME += update_crouch_jump_run_fly.c
SRC_NAME += update_rotate.c
SRC_NAME += collision.c
SRC_NAME += load_textures_2.c
SRC_NAME += home.c
SRC_NAME += ray_transparent.c
SRC_NAME += raycaster_transparent.c
SRC_NAME += raycaster_tools_2.c
SRC_NAME += map_checker_2.c

OBJ_NAME = $(SRC_NAME:.c=.o)

LIB_NAME = libft.a

INC_PATH = ./includes/
SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
LIB_PATH = ./libft/

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
HEAD = $(addprefix $(INC_PATH), $(INC_NAME))
LIB = $(addprefix $(LIB_PATH), $(LIB_NAME))

#FRAMEWORK = -framework OpenGL -framework AppKit
#MLXFLAG = -I /usr/local/include -L /usr/local/lib -lmlx
SDL2 = -lSDL2 -lSDL2_ttf
FMOD = -I fmod/inc -L fmod/lib/x86_64 -lfmod -lfmodL
COMPILE_SDL2 = SDL2_done
INSTALL_FMOD = fmod/done
# `sdl2-config --cflags --libs`
CFLAGS = -g -Wall -Wextra -Werror -lm -lpthread -D_REENTRANT -DLinux
NORMINETTE = ~/.norminette/norminette.rb

$(CC) = clang

###############################################################################

all: $(NAME)

$(NAME): $(COMPILE_SDL2) $(INSTALL_FMOD) $(OBJ)
	make -C libft/.
	$(CC) $(OBJ) $(LIB) -o $(NAME) $(SDL2) $(FMOD) $(CFLAGS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEAD) 
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< 

$(COMPILE_SDL2):
	if ! dpkg-query -W -f='$${Status}' freeglut3-dev  | grep "ok installed"; \
	then sudo apt-get -y install freeglut3-dev; fi
	(tar xf SDL2-2.0.12.tar.gz \
	&& cd SDL2-2.0.12 \
	&& touch configure \
	&& ./configure \
	&& make \
	&& sudo make install)
	if ! dpkg-query -W -f='$${Status}' libfreetype6-dev  | grep "ok installed"; \
	then sudo apt-get -y install libfreetype6-dev; fi
	(tar xf SDL2_ttf-2.0.15.tar.gz \
	&& cd SDL2_ttf-2.0.15 \
	&& touch configure \
	&& ./configure \
	&& make \
	&& sudo make install \
	&& sudo ldconfig)
	touch SDL2_done

$(INSTALL_FMOD):
	sudo cp fmod/lib/* /usr/lib
	touch fmod/done

clean:
	make clean -C $(LIB_PATH)
	$(RM) -rf $(OBJ_PATH)

fclean: clean debug_clean
	$(RM) $(LIB)
	$(RM) $(NAME)

reset_all_lib: reset_FMOD reset_SDL2

reset_SDL2:
	$(RM) SDL2_done

reset_FMOD:
	$(RM) fmod/done

re: fclean all

debug: $(COMPILE_SDL2)
	make -C $(LIB_PATH)
	$(CC) -g3 -fsanitize=address,undefined $(CFLAGS) -I $(INC_PATH) $(SRC) $(LIB) $(SDL2) $(FMOD)

debug_clean:
	$(RM) -rf a.out a.out.DSYM
	
norm:
	$(NORMINETTE) $(SRC) $(HEAD) $(LIB_PATH)

.PHONY: clean fclean re all debug debug_clean norm
