NAME		= miniRT

# コンパイラとフラグ
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -O0

# 本番用最適化フラグ全部乗せ
# -ffast-mathは計算に誤差がでることがあるので試し必要あり。
#CFLAGS		= -Wall -Wextra -Werror -O3 -march=native -ffast-math -flto

# ディレクトリ
SRCS_DIR	= srcs
OBJS_DIR	= objs
INCS_DIR	= includes
LIBFT_DIR	= libft
DEBUGS_DIR = debugs
MLX_DIR 	= minilibx-linux
MLX_REPO 	= https://github.com/42Paris/minilibx-linux.git

# ライブラリ
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
LIBS		= -L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

# インクルードパス
INCLUDES	= -I $(INCS_DIR) -I $(LIBFT_DIR)/includes -I $(MLX_DIR)

# ソースファイル
MAIN_SRCS	= $(SRCS_DIR)/main.c

FILES = vec3_1.c\
		vec3_2.c\
		mlx_action_close.c\
		render_pixel.c\
		arg_parser.c\
		error.c\
		rt_loader.c\
		timer.c\
		ray_utils.c\
		hit_sphere.c\
		hit_plane.c\
		screen_norm.c\
		object_list.c

SRCS = $(addprefix $(SRCS_DIR)/,$(FILES))

# デバッグ用ソースファイル (srcs/debugs/ に配置)
DEBUG_FILES =	debug_vec3.c\
				debug_mlx_red_square.c\
				debug_rt_loader.c\
				debug_ray.c\
				debug_intersection.c\
				debug_mlx_sphere.c

# ファイル名からターゲット名を生成
DEBUG_BINS = $(DEBUG_FILES:.c=)

# ヘッダー
HEADERS = $(INCS_DIR)/miniRT.h $(INCS_DIR)/vec3.h

# オブジェクトファイル
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
MAIN_OBJ	= $(MAIN_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEBUG_OBJS	= $(addprefix $(OBJS_DIR)/$(DEBUGS_DIR)/, $(DEBUG_FILES:.c=.o))

# 全オブジェクトファイル
ALL_OBJS	= $(OBJS) $(MAIN_OBJ)

# デフォルトターゲット
all: $(NAME)

# メインプログラムのビルド
$(NAME): $(ALL_OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LIBS) -o $@

# デバッグ用ターゲット (全て srcs/debugs/ から統一的にビルド)
$(DEBUG_BINS): %: $(OBJS) $(LIBFT) $(MLX) $(OBJS_DIR)/$(DEBUGS_DIR)/%.o
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_DIR)/$(DEBUGS_DIR)/$@.o $(LIBS) -o $@

# libftのビルド
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# norminette
norm:
	norminette $(SRCS_DIR) $(LIBFT_DIR) $(INCS_DIR) | grep -v OK

# valgrind
val:
	valgrind -s --track-fds=yes --trace-children=yes --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) $(ARGS)

# clang-tidyが分析するためのファイルcompile_commands.jsonを.vscodeフォルダに作成
# 新しい.c,.hファイルをMakefileに追加した時に実行する。
bear: clean
	bear --output .vscode/compile_commands.json -- make

# mlxのビルド (フォルダがない場合は、git clone)
$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MinilibX..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

# オブジェクトファイルのコンパイルルール
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# クリーンアップ
clean:
	@rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean: clean
	@rm -f $(NAME)
	@rm -f debug_*
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re $(DEBUG_BINS) norm bear val
