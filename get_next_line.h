/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:12 by facosta           #+#    #+#             */
/*   Updated: 2025/01/21 21:01:03 by facosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// read
# include <unistd.h>
// malloc, free
# include <stdlib.h>
// FD_SETSIZE macro i.e. maximum concurrent file descriptors
# include <sys/select.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// NOTE: this string is not necessarily valid i.e. not necessarily
// nul-terminated
typedef char *	t_string;

char *		get_next_line(int fd);
void		ft_bzero(void	*p, size_t n);
size_t		ft_strlen(t_string s);
t_string	ft_strchr(const t_string str, int c);
t_string	ft_strjoin(t_string s1, t_string s2);
// void		*ft_calloc(size_t nmemb, size_t size);

#endif
