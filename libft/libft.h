/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:13:42 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/28 14:55:50 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include "../src/cub3d.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, void *src, size_t n);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
size_t	ft_strlcat(char *dst, char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	*ft_memchr(void *s, int c, size_t n);
int		ft_memcmp(void *s1, void *s2, size_t n);
char	*ft_strnstr(char *big, char *little, size_t len);
int		ft_atoi(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(char *str);
char	*ft_substr(char *str, unsigned int start, size_t len);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(char *str);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_bzero_lib(void *s, size_t n);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
