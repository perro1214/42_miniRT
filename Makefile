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
MLX_DIR 	= minilibx-linux
MLX_REPO 	= https://github.com/42Paris/minilibx-linux.git

# ライブラリ
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
LIBS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# インクルードパス
INCLUDES	= -I$(INCS_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)

# ソースファイル
MAIN_SRCS	= $(SRCS_DIR)/main.c

SRCS		= $(SRCS_DIR)/vec3_1.c\
			  $(SRCS_DIR)/vec3_2.c\
			  $(SRCS_DIR)/mlx_action_close.c\
			  $(SRCS_DIR)/render_pixel.c

DEBUG_VEC3_SRCS = $(SRCS_DIR)/debug_vec3.c#

DEBUG_MlX_RED_SQUARE_SRCS = $(SRCS_DIR)/debug_mlx_red_square.c#

# ヘッダー

HEADERS = $(INCS_DIR)/miniRT.h $(INCS_DIR)/vec3.h

# オブジェクトファイル
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
MAIN_OBJS	= $(MAIN_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEBUG_VEC3_OBJS	= $(DEBUG_VEC3_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)#
DEBUG_MlX_RED_SQUARE_SRCS_OBJS = $(DEBUG_MlX_RED_SQUARE_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)#

# 全オブジェクトファイル
ALL_OBJS	= $(OBJS) $(MAIN_OBJS)

# デフォルトターゲット
# $(LIBFT) をNAMEの依存関係に移動
all: $(NAME)

# メインプログラムのビルド
$(NAME): $(ALL_OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LIBS) -o $(NAME)

# デバッグ用ターゲット
debug_vec3: $(ALL_OBJS) $(LIBFT) $(MLX) $(DEBUG_VEC3_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(DEBUG_VEC3_OBJS) $(LIBS) -o debug_vec3

debug_mlx_red_square: $(ALL_OBJS) $(LIBFT) $(MLX) $(DEBUG_MlX_RED_SQUARE_SRCS_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(DEBUG_MlX_RED_SQUARE_SRCS_OBJS) $(LIBS) -o debug_mlx_red_square

# libftのビルド
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# norminette
norm:
	norminette $(SRC_DIR) $(INC_DIR) | grep -v OK

# clang-tidyが分析するためのファイルcompile_command.jsonをbuildフォルダに作成
bear:
	@$(MAKE) clean
	@mkdir -p build
	@cd build && bear -- make ..

# mlxのビルド (フォルダがない場合は、git clone)
$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MinilibX..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

# オブジェクトファイルのコンパイルルール
# ヘッダーファイルを追加、ヘッダーを変更したときもコンパイルするため
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# クリーンアップ
clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean: clean
	rm -f $(NAME) debug_vec3
	rm -f debug_mlx_red_square
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug_vec3 norm
