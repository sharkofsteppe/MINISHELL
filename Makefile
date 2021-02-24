.PHONY: all clean fclean re

NAME		=	minishell
CFLAGS		=	-Wall -Wextra
RM			=	rm -f
CC			=	gcc
INC			=	-Iincludes -I.
LIB			=	-Llibft -lft
EXEC_DIR	=	srcs/executor/
EXEC_SRCS	=	minishell.c \
				utils.c \
				$(EXEC_DIR)exec_cd.c \
				$(EXEC_DIR)exec_cmd.c \
				$(EXEC_DIR)exec_echo.c \
				$(EXEC_DIR)exec_env.c \
				$(EXEC_DIR)exec_exit.c \
				$(EXEC_DIR)exec_pwd.c \
				$(EXEC_DIR)exec_setenv.c \
				$(EXEC_DIR)exec_unsetenv.c
EXEC_OBJS	=	$(EXEC_SRCS:.c=.o)
all: $(NAME)
%o : %c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
$(NAME): $(EXEC_OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(LIB) $(INC) $(EXEC_OBJS) -o $(NAME)
clean:
	$(RM) $(EXEC_OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all