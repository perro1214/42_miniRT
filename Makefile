NAME		= miniRT

CC			:= cc
# CFLAGS	:= -Wall -Wextra -Werror -g -O0
CFLAGS		:= -Wall -Wextra -Werror -O3 -march=native -ffast-math -flto

# dirctory
SRCS_DIR	 := srcs
OBJS_DIR	 := objs
INCS_DIR	 := includes
LIBFT_DIR	 := libft
DEBUGS_DIR := debugs
MLX_DIR 	 := minilibx-linux
MLX_REPO 	 := https://github.com/42Paris/minilibx-linux.git

# library
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
LIBS		= -L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

# include path
INCLUDES	= -I $(INCS_DIR) -I $(LIBFT_DIR)/includes -I $(MLX_DIR)

# source file
MAIN_SRCS	= $(SRCS_DIR)/main.c

FILES := vec3_1.c\
		vec3_2.c\
		vec3_3.c\
		mlx_action_other.c\
		mlx_action_key.c\
		mlx_action_mouse.c\
		mlx_action_move.c\
		mlx_action_reset.c\
		mlx_action_rotate.c\
		arg_parser.c\
		error.c\
		rt_loader.c\
		rt_validator.c\
		color_util.c\
		object_util.c\
		rt_parser_util.c\
		set_object.c\
		set_scene.c\
		ray_utils.c\
		hit_sphere.c\
		hit_plane.c\
		hit_cylinder.c\
		hit_cone.c\
		hit_circle.c\
		hit_util.c\
		screen_norm.c\
		render_scene.c\
		render_util.c\
		calc_ambient.c\
		calc_diffuse.c\
		calc_specular.c\
		calc_shading.c\
		shadow.c

SRCS = $(addprefix $(SRCS_DIR)/,$(FILES))

# header
HEADERS := $(INCS_DIR)/miniRT.h $(INCS_DIR)/vec3.h

# object file
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
MAIN_OBJ	= $(MAIN_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEBUG_OBJS	= $(addprefix $(OBJS_DIR)/$(DEBUGS_DIR)/, $(DEBUG_FILES:.c=.o))

# all object files
ALL_OBJS	= $(OBJS) $(MAIN_OBJ)

# default target
all: $(NAME)

# build main
$(NAME): $(ALL_OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LIBS) -o $@

# build main
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# norminette
norm:
	norminette $(SRCS_DIR) $(LIBFT_DIR) $(INCS_DIR) | grep -v OK

# valgrind
val:
	valgrind -s --track-fds=yes --trace-children=yes --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) $(ARGS)

# build mlx
$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MinilibX..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

# compile object files
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# clean up
clean:
	@rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re  norm val
