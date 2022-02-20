NAME	=	RTv1

#compiler
CC	=	gcc
LFLAGS	=	-Wall -Wextra -Werror -g

#sources & object files
SRC_DIR =	./src/
OBJ_DIR =	./build/
SRC_LIST = main.c \
		init.c \
		keys.c \
		vec_math.c \
		shape_sphere.c \
		shape_plane.c \
		shape_cylinder.c \
		shape_cone.c \
		shape_cc_shared.c \
		render.c \
		colour.c \
		ray.c \
		utils.c \
		lights.c \
		matrix_math.c \
		matrix_utils.c \
		matrix_inverse.c \
		matrix_apply.c \
		matrix_tform.c \
		matrix_rotate.c \
		parser.c \
		parse_obj.c \
		parse_light.c \
		parse_cam.c \
		camera.c \
		materials.c \
		vec_utils.c \
		print.c \
		draw.c
SRCS = $(addprefix $(SRC_DIR),$(SRC_LIST))
OBJS = $(addprefix $(OBJ_DIR),$(SRC_LIST:.c=.o))

#libft
LIBFT = libft/libft.a

#SDL2
SDL_SRC_DIR = SDL2-2.0.14
SDL_DIR = libSDL2
SDL_BUILD_DIR_PATH = $(CURDIR)/$(SDL_DIR)
SDL_CFLAGS = `$(SDL_DIR)/bin/sdl2-config --cflags --libs`
SDL_BIN = $(SDL_DIR)/lib/libSDL2.a

.PHONY: all clean fclean re

all: $(LIBFT) $(SDL_BIN) $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(LFLAGS) -Iinclude/ -Ilibft/includes -I$(SDL_DIR)/include/SDL2 -o $@ -c $<

$(LIBFT):
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(SDL_CFLAGS) -L./libft/ -lft -lm -o $(NAME)

$(SDL_BIN) :
	echo "Extracting SDL archives..."
	tar xzf SDL2-2.0.14.tar.gz
	mkdir -p $(SDL_DIR)
	cd $(SDL_SRC_DIR); ./configure --prefix=$(SDL_BUILD_DIR_PATH); make -j6; make install

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR)
	rm -rf DATA

fclean: clean
	rm $(NAME)
	rm -rf $(SDL_SRC_DIR)
	make fclean -C libft

re: fclean all
