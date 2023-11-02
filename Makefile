NAME = philo
CC = cc

CFLAGS = -Wall -Wextra  -Werror 


SRC =  \
	philo.c \
	utils.c \
	printf/ft_printf.c \
	

PRINTF			=	libftprintf.a

OBJ = $(SRC:.c=.o)
.SILENT:

all : ${NAME} 
	./cringe.sh


${NAME} : ${OBJ}
	@make -C printf
	@mv printf/libftprintf.a .
	$(CC) $(OBJ) -o $(NAME)  ${PRINTF} 
#printf '\033[32m[ ✔ ] %s\n\033[0m' "Philosophers are starting to do their unpayed duty."

.o: .c
	${CC} -c ${CFLAGS} $< -o $@

clean: 
	rm -f $(OBJ) 
	make clean -C printf
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Cleaning objects"
	
fclean: clean
	make fclean -C printf
	rm -rf ${PRINTF}
	rm -f $(NAME) 
#printf '\033[32m[ ✔ ] %s\n\033[0m' "cleanclean all"

re: fclean all

.PHONY: all clean fclean re all
