SRCS	=	main.c\
			philo.c\
			philo-constructor.c\
			philo-public.c\
			utils.c
OBJS	= $(SRCS:.c=.o)
NAME	= philo
CFLAGS	= -g3 -fsanitize=thread

all:	$(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)