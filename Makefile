NAME = philo
CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

SRC =  \
	philo.c \


OBJ = $(SRC:.c=.o)
.SILENT:

all : ${NAME}
	printf '|￣￣￣￣￣￣￣￣￣￣￣￣￣￣ |\n   '
	printf '     Are you a thread?\n '
	printf '    Because I cant wait\n '
	printf '  to share my memory with u.\n '
	printf '  🌷･.✧⁎ 🎧 🎀𓂃🦋⋆ ｡\n '
	printf '|＿＿＿＿＿＿＿＿＿＿＿＿＿＿|\n'
	printf '        \\(•◡•) /\n'
	printf '       	 \\    /\n'


${NAME} : ${OBJ}
	$(CC) $(OBJ) -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Philosophers are starting to do their unpayed duty lol "

.o: .c
	${CC} -c ${CFLAGS} $< -o $@

clean: 
	rm -f $(OBJ) 
	printf '\033[32m[ ✔ ] %s\n\033[0m' "cleanclean"
	
fclean: clean
	rm -f $(NAME) 
	printf '\033[32m[ ✔ ] %s\n\033[0m' "cleanclean all"

re: fclean all

.PHONY: all clean fclean re all
