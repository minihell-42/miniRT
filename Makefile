NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBS = -lXext -lX11 -lm -L $(MLX_DIR) -lmlx
INC = -I ./includes/ -I ./libft/ -I $(MLX_DIR)

SRC_DIR = srcs/
OBJ_DIR = obj/

MLX_DIR = minilibx/
MLX_NAME = libmlx.a
MLX = $(MLX_DIR)$(MLX_NAME)

LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/errors.c $(SRC_DIR)/init.c $(SRC_DIR)/parser/read.c

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
      fi
	@$(MAKE) -C $(MLX_DIR)
	
$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBFT) $(INC) $(LIBS)
      
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_DIR)$(LIBFT_NAME)
	@if [ -d "$(MLX_DIR)" ]; then \
		rm -rf $(MLX_DIR); \
	fi

re:		fclean all

.PHONY: all clean fclean re