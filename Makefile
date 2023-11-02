CC            = gcc
CFLAGS        = -Wextra -Wall -Werror -g3 -pthread -fsanitize=thread
NAME        = philo

OBJ_PATH     = obj/

SRC            = philo.c \
            utils.c

OBJ        = $(SRC:.c=.o)
OBJS    = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME)
	./cringe.sh
.SILENT:
$(OBJ_PATH)%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(LIBFT) $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re