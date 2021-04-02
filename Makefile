NAME	=	minishell
SRCDIR	=	srcs/
EXECSDIR=	srcs/execs/
LIBFTDIR=	libft/
UTILSDIR=	srcs/utils/
PARSERDIR=	srcs/parser/
LIBFT	=	${LIBFTDIR}libft.a
HEADERS	=	includes/minishell.h libft/libft.h
SRCS	=	${addprefix ${SRCDIR},		minishell.c}
EXCS	=	${addprefix ${EXECSDIR},	e_cd.c \
										e_echo.c \
										e_env.c \
										e_export.c \
										e_pwd.c \
										e_unset.c \
										e_promt.c \
										e_signal.c \
										e_exit.c \
										e_cmd.c \
										e_redd.c \
										e_pipe.c \
										history.c \
										ter.c}
UTILS	=	${addprefix ${UTILSDIR},	e_error.c \
										e_free.c \
										e_utils.c \
										e_sort_envp.c \
										rdr_check.c \
										rdr_utils.c \
										cd_utils.c \
										env_utils.c \
										env_utils1.c \
										export_utils.c \
										cmd_utils.c \
										rdr_utils1.c \
										ter_utils.c \
										handle.c \
										handle1.c}
PARSER	=	${addprefix ${PARSERDIR},	processing.c \
										process_utils.c \
										processing_ponctions.c \
										rdrextract.c \
										rdrponctions.c \
										rdrutils.c \
										analyze.c \
										analyze_utils.c \
										analyze_ponctions.c \
										arguments.c \
										argument_utils.c \
										argument_ponctions.c \
										comanda.c \
										comanda_ponctions.c \
										litter.c}
OBJS	=	${SRCS:.c=.o} ${UTILS:.c=.o} ${PARSER:.c=.o} ${EXCS:.c=.o}
LIBS	=	-ltermcap -Llibft -lft
INCL	=	-Iincludes -Ilibft
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm
MAKES	=	makes
all: ${MAKES} ${NAME}
${NAME}: ${OBJS} ${HEADERS} ${LIBFT} Makefile
	${CC} ${CFLAGS} ${INCL} ${LIBS} ${OBJS} -o ${NAME}
${MAKES}:
	@${MAKE} -sC ${LIBFTDIR}
%.o : %.c ${HEADERS}
	${CC} -c ${CFLAGS} ${INCL} $< -o $@
${LIBFT}:
	@${MAKE} -sC ${LIBFTDIR}
clean:
	@${MAKE} -sC ${LIBFTDIR} clean
	${RM} -f ${OBJS}
fclean: clean
	@${MAKE} -sC ${LIBFTDIR} fclean
	${RM} -f ${NAME}
re:	fclean all
.PHONY: all clean fclean re
