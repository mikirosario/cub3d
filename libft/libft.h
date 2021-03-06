/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 00:30:21 by mrosario          #+#    #+#             */
/*   Updated: 2020/07/21 20:27:46 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <stdlib.h>
# include <wchar.h>
# include "./printf/libftprintf.h"

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
	size_t			len;
}				t_list;

void			*ft_memset(void *b, int c, size_t len);
void			*ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, void const *src, size_t n);
void			*ft_memccpy(void *dst, void const *src, int c, size_t n);
void			*ft_memmove(void *dst, void const *src, size_t len);
void			*ft_memchr(void const *s, int c, size_t n);
int				ft_memcmp(void const *s1, void const *s2, size_t n);
int				ft_chrcmp(char *s1, char c);
size_t			ft_strlen(char const *s);
size_t			ft_wstrlen(wchar_t const *s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_thousep(char *numstr, char sep);
char			*ft_strtolower(char *str);
char			*ft_strchr(char const *s, int c);
char			*ft_strrchr(char const *s, int c);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
size_t			ft_strlcpy(char *dst, char const *src, size_t dstsize);
size_t			ft_strlcat(char *dst, char const *src, size_t dstsize);
char			*ft_strnstr(char const *hay, char const *needle, size_t len);
int				ft_atoi(char const *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(char const *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_itoa_base(long long int num, int base);
char			*ft_llitoa(long long int n);
char			*ft_llitoa_base(long long int num, int base);
char			*ft_lluitoa(unsigned long long int n);
char			*ft_lluitoa_base(unsigned long long int num, int base);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar(char const c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
size_t			ft_putstr(char const *str, size_t len);
size_t			ft_wputstr(wchar_t const *str, size_t len);
void			ft_filler(char c, size_t n);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *));
int				ft_get_next_line(int fd, char **line);
char			*ft_skipspaces(const char *line);
char			*ft_skipdigits(const char *line);

#endif
