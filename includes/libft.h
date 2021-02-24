/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezachari <ezachari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:33:16 by gesperan          #+#    #+#             */
/*   Updated: 2021/02/24 18:01:52 by ezachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# define NEW_LINER '\n'
# define END_STRING '\0'
# define TRUE 1
# define FALSE -1
# define ENDLINE_TOUCHED 1
# define ENDLINE_NOT_FOUND 0
# define EOF_REACHED 0
# define ERROR -1
# define BUFFER_SIZE 32

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

enum				e_errorlist
{
	ERR_0 = -100,
	ERR_1,
	ERR_2,
	ERR_3,
	ERR_4,
	ERR_5,
	ERR_6,
	ERR_7,
	ERR_8,
	ERR_9,
	ERR_10,
	ERR_11
};

int					get_next_line(int fd, char **line);
int					finder(const char *str, const char c);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strchr(const char *str, int c);
char				*ft_strdup(const char *source);
size_t				ft_strlcat(char *dst, char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
char				*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char				*ft_strrchr(const char *str, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
int					ft_ps_cub(char *s, int fd, int err);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
char				*ft_strjoin(char const *str1, char const *str2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *str, char c);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
char				*ft_itoa_ptr(unsigned long long n);
char				*ft_itoa_ui(unsigned int n);
char				*ft_itoa_base(size_t num);
void				ft_zeroer(char *s, char c, int len);
int					ft_errich(int a);
int					ps_cub(char *s, int fd, int err);
char				*ft_fillstr(char c, int len);
int					size_arr(char **str);
void				*ft_memory_free(char **str, size_t count);
int					finder(const char *str, const char c);
#endif