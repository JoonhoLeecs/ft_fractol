CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXDIR = ./minilibx_mms/
MLXINC = ./minilibx_mms/
MLX = libmlx.dylib
LIBFTDIR = ./libft/
LIBFT = libft.a
SRC = fractol.c \
		ft_strcmp.c
# SRC_BONUS = pipex_bonus.c \
# 		pipex2_bonus.c \
# 		pipex3_bonus.c \
# 		heredoc_bonus.c \
# 		getnextline/get_next_line.c \
# 		getnextline/get_next_line_utils.c \
		ft_strcmp_bonus.c
OBJECTS = $(SRC:.c=.o)
# OBJECTS_BONUS = $(SRC_BONUS:.c=.o)
HEADER = fractol.h libft/libft.h minilibx_mms/mlx.h
HEADER_BONUS = pipex_bonus.h libft/libft.h getnextline/get_next_line.h
NAME = fractol

.PHONY: all bonus clean fclean re

# all : $(NAME)
all : MAKE_ALL

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -O -I $(MLXINC)

$(NAME) : MAKE_ALL

MAKE_ALL : $(MLX) $(LIBFT) $(OBJECTS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -lm -L. -lmlx -L. -lft -framework OpenGL -framework AppKit
			@touch MAKE_ALL
#			@rm -f MAKE_BONUS

$(MLX) :
	$(MAKE) -C $(MLXDIR)
	cp $(MLXDIR)$(MLX) .

$(LIBFT) :
	$(MAKE) bonus -C $(LIBFTDIR)
	cp $(LIBFTDIR)/$(LIBFT) $(LIBFT)

# bonus : MAKE_BONUS

# MAKE_BONUS : $(LIBFT) $(OBJECTS_BONUS) $(HEADER_BONUS)
# 			cc $(CFLAGS) $(OBJECTS_BONUS) -o $(NAME) -L. -lft
# 			@touch MAKE_BONUS
# 			@rm -f MAKE_ALL

clean :
	$(MAKE) clean -C $(LIBFTDIR)
	rm -f $(OBJECTS)
	rm -f $(LIBFT)
	rm -f $(MLX)
	@rm -f MAKE_ALL MAKE_BONUS
# rm -f $(OBJECTS_BONUS)

fclean :
	$(MAKE) fclean -C $(LIBFTDIR)
	$(MAKE) clean -C $(MLXINC)
	$(MAKE) clean
	rm -f $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all
