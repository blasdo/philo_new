SRCS	=	main.c\
			philo.c\
			philo-constructor.c\
			philo-public.c\
			philo-public-boolean.c\
			inspector.c\
			argument-control.c\
			utils.c

OBJS	= $(SRCS:.c=.o)
NAME	= philo
CFLAGS	= -Wall -Wextra -Werror
all:	$(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)