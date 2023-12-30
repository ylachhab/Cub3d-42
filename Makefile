NAME = cub3D

NAME_B = cub3D_bonus

CC = cc -g

FLAGS = -Wall -Werror -Wextra

SRCS =	src/main.c \
		src/parcing/parcing.c \
		src/parcing/parcing_utils.c \
		src/parcing/parcing_utils1.c \
		src/parcing/parcing_utils2.c \
		src/parcing/parcing_utils3.c \
		src/parcing/parcing_utils4.c \
		src/draw.c \
		src/draw_utils.c \
		src/draw_utils1.c \
		src/draw_utils2.c \
		src/draw_utils3.c \
		src/move.c \
		src/move_utils.c

SRCB =	bonus/main_bonus.c \
		bonus/parcing/parcing_bonus.c \
		bonus/parcing/parcing_utils_bonus.c \
		bonus/parcing/parcing_utils1_bonus.c \
		bonus/parcing/parcing_utils2_bonus.c \
		bonus/parcing/parcing_utils3_bonus.c \
		bonus/parcing/parcing_utils4_bonus.c \
		bonus/draw_bonus.c \
		bonus/draw_utils_bonus.c \
		bonus/draw_utils1_bonus.c \
		bonus/draw_utils2_bonus.c \
		bonus/draw_utils3_bonus.c \
		bonus/move_bonus.c \
		bonus/move_utils_bonus.c

OBJS = $(SRCS:.c=.o)

OBJB = $(SRCB:.c=.o)

all : libft gnl mlx $(NAME)

bonus : libft gnl mlx $(NAME_B)

libft :
	make -C ./libft all

gnl :
	make -C gnl all

mlx :
	make -C mlx all

src/%.o: src/%.c src/cub3d.h
	$(CC) $(FLAGS) -c $< -o $@

bonus/%.o: bonus/%.c bonus/cub3d_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) libft/libft.a gnl/libftgnl.a mlx/libmlx.a -lmlx -framework OpenGl -framework Appkit -o $(NAME)

$(NAME_B): $(OBJB)
	$(CC) $(FLAGS) $(OBJB) libft/libft.a gnl/libftgnl.a mlx/libmlx.a -lmlx -framework OpenGl -framework Appkit -o $(NAME_B)

clean:
	rm -rf $(OBJS) $(OBJB)
	make  -C libft clean
	make  -C gnl clean
	make  -C mlx clean

fclean:	clean
	rm -rf $(NAME) $(NAME_B)
	make  -C libft fclean
	make  -C gnl fclean

re : fclean all

.PHONY : libft gnl re clean fclean all