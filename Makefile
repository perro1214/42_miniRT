NAME		= miniRT

# コンパイラとフラグ
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# ディレクトリ
SRCS_DIR	= srcs
OBJS_DIR	= objs
INCS_DIR	= includes
LIBFT_DIR	= libft

# ライブラリ
LIBFT		= $(LIBFT_DIR)/libft.a
LIBS		= -L$(LIBFT_DIR) -lft -lm

# インクルードパス
INCLUDES	= -I$(INCS_DIR) -I$(LIBFT_DIR)/includes

# ソースファイル
MAIN_SRCS	= $(SRCS_DIR)/main.c

SRCS		= $(SRCS_DIR)/vec3.c

DEBUG_VEC3_SRCS = $(SRCS_DIR)/debug_vec3.c

# オブジェクトファイル
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
MAIN_OBJS	= $(MAIN_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEBUG_VEC3_OBJS	= $(DEBUG_VEC3_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# 全オブジェクトファイル
ALL_OBJS	= $(OBJS) $(MAIN_OBJS)

# デフォルトターゲット
all: $(LIBFT) $(NAME)

# メインプログラムのビルド
$(NAME): $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LIBS) -o $(NAME)

# デバッグ用ターゲット
debug_vec3: $(LIBFT) $(OBJS) $(DEBUG_VEC3_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(DEBUG_VEC3_OBJS) $(LIBS) -o debug_vec3

# libftのビルド
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# オブジェクトファイルのコンパイルルール
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# クリーンアップ
clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) debug_vec3
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug_vec3
