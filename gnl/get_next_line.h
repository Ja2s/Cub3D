/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:32:58 by jgavairo          #+#    #+#             */
/*   Updated: 2024/08/28 14:55:37 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int			ft_read_file(int fd, char static_buff[], char **res);
int			ft_back_static(char static_buff[]);
int			ft_move_static(char static_buff[], char **res);
int			tmp_len(char *tmp, int choice);
int			endline_checker(char *buff);
char		*get_next_line(int fd);
char		*ft_strjoin(char *s1, char *s2);
void		ft_free(char static_buff[], char **res);
void		ft_bzero(void *s, size_t n, size_t start);
void		*ft_memmove(void *dest, const void *src, size_t n);

#endif
