# Program name
NAME	=	philo

# Compiler settings
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror # -g -fsanitize=thread

#debug : setarch $(uname -m) -R

# Source files
SRCS =	main.c \
		validata.c \
		init.c \
		monitor.c \
		routine.c \
		routine_helper.c \
		check.c \
		time.c \
		utils.c

# Object files
OBJS	=	$(SRCS:.c=.o)

# Build rules
all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Clean rules
clean	:
	rm -f $(OBJS)

fclean	:	clean
	rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re