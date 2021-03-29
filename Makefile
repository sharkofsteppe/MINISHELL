SRCDIR	=	srcs/
LIBFTDIR=	libft/
UTILSDIR=	utils/
PARSERDIR=	parse/
LIBFT	=	${LIBFTDIR}libft.a
HEADERS	=	${addprefix includes/, minishell.h}
NAME	=	minishell
SRCS	=	${addprefix ${SRCDIR}, e_cd.c e_echo.c e_env.c e_export.c e_pwd.c e_unset.c e_promt.c e_signal.c e_exit.c e_cmd.c e_redd.c}
UTILS	=	${addprefix ${SRCDIR}${UTILSDIR}, e_error.c e_free.c e_utils.c e_sort_envp.c}
PARSER	=	minishell.c processing.c process_utils.c rdrextract.c processing_ponctions.c \
			rdrponctions.c rdrutils.c analyze.c analyze_utils.c \
			analyze_ponctions.c arguments.c argument_utils.c argument_ponctions.c \
			comanda.c comanda_ponctions.c
OBJS	=	${SRCS:.c=.o} ${UTILS:.c=.o} ${PARSER:.c=.o}
LIBS	=	-ltermcap -Llibft -lft
INCL	=	-Iincludes -Ilibft
CC		=	gcc
CFLAGS	=	-Wall -Wextra
RM		=	rm
MAKES	=	makes
all: ${MAKES} ${NAME}
${NAME}: ${OBJS} ${HEADERS} ${LIBFT} Makefile
	${CC} ${CFLAGS} ${INCL} ${LIBS} ${OBJS} -o ${NAME}
${MAKES}:
	@${MAKE} -sC ${LIBFTDIR}
%.o : %.c ${HEADERS}
	@${CC} -c ${CFLAGS} ${INCL} $< -o $@
${LIBFT}:
	@${MAKE} -sC ${LIBFTDIR}
clean:
	@${MAKE} -sC ${LIBFTDIR} clean
	@${RM} -f ${OBJS}
fclean: clean
	@${MAKE} -sC ${LIBFTDIR} fclean
	@${RM} -f ${NAME}
re:	fclean all
.PHONY: all clean fclean re
