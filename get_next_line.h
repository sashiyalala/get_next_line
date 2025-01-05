/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:12 by facosta           #+#    #+#             */
/*   Updated: 2025/01/05 16:04:38 by facosta          ###   ########.fr       */
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
typedef char *	string;

string	get_next_line(int fd);
// TODO: Change all char * in declarations to "string"
void	gnl_strjoin(string *p_s1, string s2);
string	gnl_strchr(string s, int c);
size_t	gnl_strlen(string s);
size_t	gnl_strlcpy(string dest, string src, size_t size);
string	gnl_substr(string s, unsigned int start, size_t len);

#endif
