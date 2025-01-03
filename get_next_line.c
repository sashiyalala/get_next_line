/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:18 by facosta           #+#    #+#             */
/*   Updated: 2025/01/03 21:38:49 by facosta          ###   ########.fr       */
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

static void	move_remainder_to_buffer(string *p_line, string buffer)
{
	ssize_t	remainder_len;
	size_t	line_len;
	string	line;

	line = *p_line;
	line_len = 0;
	while (line[line_len] != '\n' && line[line_len])
		line_len++;
	if (line[line_len] == '\n') // si he parado por encontrarme un salto de linea, añade uno mas a la len
		line_len++;
	remainder_len = (gnl_strlen(line) - line_len);
	if (remainder_len != 0) //i.e. if there is some remainder (i.e. len not 0)
		gnl_strlcpy(buffer, line + line_len, remainder_len + 1); // copy the contents of line, starting right after the \n, onto buffer
	else
		buffer[0] = '\0';
	// OBS: note how there is no chance of the remainder not fitting entirely
	// in the buffer var, as the remainder has at most buffer-len length
	line = gnl_substr(line, 0, line_len + 1);
	free(*p_line);
	*p_line = line;
}

static void	read_until_newline_in_buffer(int fd, string *p_line, string buffer)
{
	ssize_t	read_len; // we use ssize_t to allow for negative numbers, as read can be <0
	string	composed_line;

	composed_line = malloc(1 * sizeof(char));
	if (!composed_line)
		return ;
	composed_line[0] = '\0';
	read_len = BUFFER_SIZE;
	// while there is no newline in buffer and we've been able to read as many
	// bytes as we want
	while (!(gnl_strchr(buffer, '\n')) && read_len == BUFFER_SIZE)
	{
		// continue to read, and document how many bytes you've been able 2 read
		read_len = read(fd, buffer, BUFFER_SIZE);
		if ((read_len < 0)|| (read_len == 0 && !composed_line[0]))
		{
			// Cuando falla la lectura o encuentro final de archivo, tienes que
			// devolver NULL en gnl (x el enunciado)
			free(composed_line);
			free(*p_line);
			*p_line = NULL;
			return ;
		}
		buffer[read_len] = '\0'; // convert the buffer to a "valid string"
		gnl_strjoin(&composed_line, buffer);
	}
	free(*p_line);
	*p_line = composed_line;
}

// Main function is just in charge of doing some clearing checks and allocating
// 1byte into the resulting line variable->just to initialize it to something
char	*get_next_line(int fd)
{
	char	*line;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (0);

	line = malloc(1 * sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (buffer[0] != '\0') // i.e. buffer contains some "remainder" from reading the line before
	{
		gnl_strjoin(&line, buffer);
		if (!gnl_strchr(buffer, '\n'))  //&& (gnl_strchr(buffer, '\0') == (buffer + BUFFER_SIZE)))
		{
			read_until_newline_in_buffer(fd, &line, buffer);
			if (!line)
				return (0);
		}
	}
	else  // cuando aun no hay nada en el buffer
	{
		read_until_newline_in_buffer(fd, &line, buffer);
		if (!line)
			return (0);
	}
	move_remainder_to_buffer(&line, buffer);
	return (line);
}
