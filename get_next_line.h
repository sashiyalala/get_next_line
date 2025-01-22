/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:12 by facosta           #+#    #+#             */
/*   Updated: 2025/01/22 18:47:55 by facosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// read
# include <unistd.h>
// malloc, free
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// NOTE: this string is not necessarily valid i.e. not necessarily
// nul-terminated
typedef char *	t_string;

char		*get_next_line(int fd);
void		gnl_strjoin(t_string *p_s1, t_string s2);
t_string	gnl_strchr(t_string s, int c);
size_t		gnl_strlen(t_string s);
size_t		gnl_strlcpy(t_string dest, t_string src, size_t size);
t_string	gnl_substr(t_string s, unsigned int start, size_t len);

#endif
