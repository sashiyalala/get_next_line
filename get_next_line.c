/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:18 by facosta           #+#    #+#             */
/*   Updated: 2025/01/05 15:53:07 by facosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

// Given a line(by reference), trim everything after the first \n and overwrite
// the contents of buffer with the remainder
// E.g.,
// *p_line = "En un lugar de la mancha, de cuyo nombre\nno quiero\nacordarme\n"
// -->     = "En un lugar de la mancha, de cuyo nombre\n"
// buffer  = "nombre\nno quiero\nacordarme"
// -->     = "no quiero\nacordarme"
// OBS: as we only mean to pass a static variable as buffer, the original
// buffer still gets overwritten even though you are not passing it by ref.
static void	move_remainder_to_buffer(string *p_line, string buffer)
{
	ssize_t	remainder_len;
	size_t	line_len;
	string	line;

	line = *p_line;
	line_len = 0;
	while (line[line_len] != '\n' && line[line_len])
		line_len++;
	if (line[line_len] == '\n')
		line_len++;
	remainder_len = (gnl_strlen(line) - line_len);
	if (remainder_len != 0)
		gnl_strlcpy(buffer, line + line_len, remainder_len + 1);
	else
		buffer[0] = '\0';
	line = gnl_substr(line, 0, line_len + 1);
	free(*p_line);
	*p_line = line;
}

// Read chunks of size BUFFER_SIZE until you find \n, EOF or there is an error
// during reading. Every chunk you read is appended to composed_line and when
// you've stopped reading, put that composed_line into line (passed by ref).
// E.g., at the end, results will be sth like this:
// *p_line = "En un lugar de la mancha, de cuyo nombre\nno quiero\nacordarme\n"
// buffer  = "nombre\nno quiero\nacordarme"
// NOTE: The buffer will be a "valid" string, i.e. nul-terminated
// NOTE: We use type `ssize_t` for read_bytes to allow for negative numbers
// which would mean the read failed
static void	read_until_newline_in_buffer(int fd, string *p_line, string buffer)
{
	ssize_t	read_bytes;
	string	composed_line;

	composed_line = malloc(1 * sizeof(char));
	if (!composed_line)
	{
		free(*p_line);
		*p_line = NULL;
		return ;
	}
	composed_line[0] = '\0';
	gnl_strjoin(&composed_line, *p_line);
	read_bytes = 1;
	while (!(gnl_strchr(composed_line, '\n')) && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if ((read_bytes < 0) || (read_bytes == 0 && !composed_line))
		{
			free(composed_line);
			free(*p_line);
			*p_line = NULL;
			return ;
		}
		if (read_bytes == 0 && composed_line[0] == '\0')
		{
			free(composed_line);
			free(*p_line);
			*p_line = NULL;
			return ;
		}
		buffer[read_bytes] = '\0';
		gnl_strjoin(&composed_line, buffer);
	}
	free(*p_line);
	*p_line = composed_line;
}

// * Some initial checks
// * allocating 1byte into the resulting line variable, just to initialize it
//   to something
// * if the buffer contains stuff, i.e. a remainder from reading a previous
//   line => put its contents in line
char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = malloc(1 * sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (buffer[0] != '\0')
		gnl_strjoin(&line, buffer);
	read_until_newline_in_buffer(fd, &line, buffer);
	if (!line)
		return (0);
	move_remainder_to_buffer(&line, buffer);
	return (line);
}
