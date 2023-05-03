CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXDIR = ./minilibx_mms/
MLXINC = ./minilibx_mms/
MLX = libmlx.dylib
LIBFTDIR = ./libft/
LIBFT = libft.a
SRC = fractol.c \
		ft_strcmp.c \
		fractol_hook.c \
		fractol_hook2.c \
		fractol_hook3.c \
		fractol_img.c \
		fractol_palette.c \
		fractol_palette2.c \
		fractol_set.c
SRC_BONUS = fractol_bonus.c \
		ft_strcmp_bonus.c \
		fractol_hook_bonus.c \
		fractol_hook2_bonus.c \
		fractol_hook3_bonus.c \
		fractol_img_bonus.c \
		fractol_palette_bonus.c \
		fractol_palette2_bonus.c \
		fractol_set_bonus.c
OBJECTS = $(SRC:.c=.o)
OBJECTS_BONUS = $(SRC_BONUS:.c=.o)
HEADER = fractol.h libft/libft.h minilibx_mms/mlx.h
HEADER_BONUS = fractol_bonus.h libft/libft.h minilibx_mms/mlx.h
NAME = fractol

.PHONY: all bonus clean fclean re

all : MAKE_ALL

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -O -I $(MLXINC)

$(NAME) : MAKE_ALL

MAKE_ALL : $(MLX) $(LIBFT) $(OBJECTS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -lm -L. -lmlx \
			-L. -lft -framework OpenGL -framework AppKit
			@touch MAKE_ALL
			@rm -f MAKE_BONUS

$(MLX) :
	$(MAKE) -C $(MLXDIR)
	cp $(MLXDIR)$(MLX) .

$(LIBFT) :
	$(MAKE) bonus -C $(LIBFTDIR)
	cp $(LIBFTDIR)/$(LIBFT) $(LIBFT)

bonus : MAKE_BONUS

MAKE_BONUS : $(MLX) $(LIBFT) $(OBJECTS_BONUS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJECTS_BONUS) -o $(NAME) -lm -L. -lmlx \
			-L. -lft -framework OpenGL -framework AppKit
			@touch MAKE_BONUS
			@rm -f MAKE_ALL

clean :
	$(MAKE) clean -C $(LIBFTDIR)
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_BONUS)
	rm -f $(LIBFT)
	rm -f $(MLX)
	@rm -f MAKE_ALL MAKE_BONUS

fclean :
	$(MAKE) fclean -C $(LIBFTDIR)
	$(MAKE) clean -C $(MLXINC)
	$(MAKE) clean
	rm -f $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all
