NAME = cub3d

CC = cc -g

FLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

SRCS =	main.c \
		parcing/parcing.c \
		parcing/parcing_utils.c \
		parcing/parcing_utils1.c \
		parcing/parcing_utils2.c \
		parcing/parcing_utils3.c \
		parcing/parcing_utils4.c \
		draw.c \
		draw_utils.c \
		draw_utils1.c \
		move.c \
		move_utils.c

OBJS = $(SRCS:.c=.o)

all : libft gnl mlx $(NAME)

libft :
	make -C ./libft all

gnl :
	make -C gnl all

mlx :
	make -C mlx all

%.o: %.c cub3d.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) libft/libft.a gnl/libftgnl.a mlx/libmlx.a -lmlx -framework OpenGl -framework Appkit -o $(NAME)

clean:
	rm -rf $(OBJS)
	make  -C libft clean
	make  -C gnl clean
	make  -C mlx clean

fclean:	clean
	rm -rf $(NAME)
	make  -C libft fclean
	make  -C gnl fclean

re : fclean all

.PHONY : libft gnl re clean fclean all