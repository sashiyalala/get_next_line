/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:18 by facosta           #+#    #+#             */
/*   Updated: 2025/01/03 01:38:16 by facosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char	*move_remainder_to_buffer(char *line, char *buffer)
{
	ssize_t	remainder_len;
	size_t	line_len;

	line_len = 0;
	while (line[line_len] != '\n' && line[line_len])
		line_len++;
	if (line[line_len] == '\n') // si he parado por encontrarme un salto de linea, añade uno mas a la len
		line_len++;
	remainder_len = (gnl_strlen(line) - line_len);
	if (remainder_len != '\0') //i.e. if there is some remainder (i.e. len not 0)
		gnl_strlcpy(buffer, line + line_len, remainder_len + 1); // copy the contents of line, starting right after the \n, onto buffer
	else
		buffer[0] = '\0';
	// OBS: note how there is no chance of the remainder not fitting entirely
	// in the buffer var, as the remainder has at most buffer-len length
	return (gnl_substr(line, 0, line_len + 1));
}

static char	*read_until_newline_in_buffer(int fd, char *line, char *buffer)
{
	ssize_t	read_len; // we use ssize_t to allow for negative numbers, as read can be <0

	read_len = BUFFER_SIZE;
	// while there is no newline in buffer and we've been able to read as many
	// bytes as we want
	while (!(gnl_strchr(buffer, '\n')) && read_len == BUFFER_SIZE)
	{
		// continue to read, and document how many bytes you've been able 2 read
		read_len = read(fd, buffer, BUFFER_SIZE);
		buffer[read_len] = '\0'; // convert the buffer to a "valid string"
		if (read_len <= 0 && !line[0])
		{
			// if the read went wrong and line starts with 0, i.e. we haven't
			// started reading
			free(line);
			return (0);
		}
		line = gnl_strjoin(line, buffer);
	}
	return (line);
}

char	*read_line_from_file(int fd)
{
	char	*line;
	static char	buffer[BUFFER_SIZE + 1];

	line = malloc(1);
	if (!line)
		return (NULL);
	if (buffer[0] != '\0') // i.e. buffer contains some "remainder" from reading the line before
		line = gnl_strjoin(line, buffer);
	line = read_until_newline_in_buffer(fd, line, buffer);
	if (!line)
		return (0);
	return (move_remainder_to_buffer(line, buffer));
}

// Main function is just in charge of doing some clearing checks and allocating
// 1byte into the resulting line variable->just to initialize it to something
char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (0);
	return (read_line_from_file(fd));
}
