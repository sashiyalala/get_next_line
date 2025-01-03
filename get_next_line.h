/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:12 by facosta           #+#    #+#             */
/*   Updated: 2025/01/03 20:16:55 by facosta          ###   ########.fr       */
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

// NOTE: this string is not necessarily valid i.e. not necessarily nul-terminated
typedef char *	string;

char	*get_next_line(int fd);
// TODO: Change all char * in declarations to "string"
void	gnl_strjoin(string *p_s1, string s2);
char	*gnl_strchr(char *s, int c);
size_t	gnl_strlen(char *s);
size_t	gnl_strlcpy(char *dest, char *src, size_t size);
char	*gnl_substr(char *s, unsigned int start, size_t len);

#endif
