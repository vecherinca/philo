NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC_1 =  \
	./ft_printf.c \
	./ft_putchar_fd.c \
	./ft_putstr_fd.c \
	./ft_itoa.c \
	./ft_itoa_unsign.c \
	./count_hex.c \
	./count_hex_p.c \
	./ft_fornums.c \


SRC = \
	$(SRC_1)	\

OBJ = $(SRC:.c=.o)
.SILENT:
AR = ar -rc

all : ${NAME}

${NAME} : ${OBJ}
	${AR} ${NAME} ${OBJ}

.o: .c
	${CC} -c ${CFLAGS} $< -o $@


clean: 
	rm -f $(OBJ) $(BONUS_OBJ)
	
fclean: clean
	rm -f $(NAME)

re: fclean ${NAME}

.PHONY: all clean fclean re all bonus