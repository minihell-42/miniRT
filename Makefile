NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx/
LIBS = -lXext -lX11 -lm -L $(MLX_DIR) -lmlx

MLX_NAME = libmlx.a
MLX = $(MLX_DIR)$(MLX_NAME)

SRC_DIR = srcs/
OBJ_DIR = obj/
LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)

INC = -I ./includes/ \
      -I ./libft/ \
      -I $(MLX_DIR)

SRC = $(SRC_DIR)/main.c \

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)
	
$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBFT) $(INC) $(LIBS)
      
clean:
	@rm -rf $(OBJ_DIR)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_DIR)$(LIBFT_NAME)

re:		fclean all

.PHONY: all clean fclean re