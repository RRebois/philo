# VARIABLES
NAME		=	philo

CC			=	cc

RM			=	rm -rf

FLAGS		=	-Wall -Wextra -Werror -pthread #-fsanitize=thread -O2 -g3#-fsanitize=address

HEADER		=	philo.h


# DIRECTORIES
D_HEADER	=	incs/

D_SRCS		=	SRCS/

D_OBJS		=	objs/


# FILES SO_LONG
LST_SRCS		=	main.c \
					data.c \
					utils.c \
					routine.c \
					time.c \
					death.c \
					free.c \
					actions.c

LST_OBJS	=	$(LST_SRCS:.c=.o)

SRCS		=	$(addprefix $(D_SRCS), $(LST_SRCS))

INCS		=	$(addprefix $(D_HEADER), $(HEADER))

OBJS		=	$(addprefix $(D_OBJS), $(LST_OBJS))


# RULES
all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(OBJS) $(FLAGS) -o $(NAME)

$(D_OBJS)%.o	:	$(D_SRCS)%.c $(INCS) Makefile
					mkdir -p $(D_OBJS)
					$(CC) $(FLAGS) -I $(D_HEADER) -c $< -o $@

clean	:
			$(RM) $(OBJS)
			$(RM) $(D_OBJS)

fclean	:
			$(MAKE) clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re lib bonus
