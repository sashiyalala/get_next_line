/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:18 by facosta           #+#    #+#             */
/*   Updated: 2025/01/22 19:39:52 by facosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(t_string s)
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
static void	move_remainder_to_buffer(t_string *p_line, t_string buffer)
{
	ssize_t		remainder_len;
	size_t		line_len;
	t_string	line;

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

// Given the two dynamically allocated t_strings, free their memory
// * composed_lined passed by value, only free if it's not pointing
//	 NULL already
// * p_line, a pointer to the gnl variable "line", free its contents, i.e.
//   the line.
static void	free_line_pointers(t_string composed_line, t_string *p_line)
{
	if (composed_line != NULL)
		free(composed_line);
	free(*p_line);
	*p_line = NULL;
}

// Read chunks of size BUFFER_SIZE until you find an end of line, i.e.:
// \n, EOF or there is an error during reading.
// Every chunk you read is appended to composed_line and when
// you've stopped reading, put that composed_line into line (passed by ref).
// E.g., at the end, results will be sth like this:
// *p_line = "En un lugar de la mancha, de cuyo nombre\nno quiero\nacordarme\n"
// buffer  = "nombre\nno quiero\nacordarme"
// * The buffer will be a "valid" string, i.e. nul-terminated
// * We use type `ssize_t` for read_bytes to allow for negative numbers
//   which would mean the read failed
static void	read_until_eol_in_buffer(int fd, t_string *p_line, t_string buffer)
{
	ssize_t		read_bytes;
	t_string	composed_line;

	composed_line = malloc(1 * sizeof(char));
	if (!composed_line)
		return (free_line_pointers(composed_line, p_line));
	composed_line[0] = '\0';
	gnl_strjoin(&composed_line, *p_line);
	read_bytes = 1;
	while (!(gnl_strchr(composed_line, '\n')) && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if ((read_bytes < 0) || (read_bytes == 0 && !composed_line))
			return (free_line_pointers(composed_line, p_line));
		if (read_bytes == 0 && composed_line[0] == '\0')
			return (free_line_pointers(composed_line, p_line));
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
	t_string	line;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = malloc(1 * sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (buffer[0] != '\0')
		gnl_strjoin(&line, buffer);
	read_until_eol_in_buffer(fd, &line, buffer);
	if (!line)
		return (0);
	move_remainder_to_buffer(&line, buffer);
	return (line);
}

// #include "get_next_line.h"
// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>

// int main()
// {
	// {
	// 	int fd = open("read_test.txt", O_RDONLY);
	// 	char *line = get_next_line(fd);
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	free(line);
	// }

	// {
	// 	t_string	name = "read_error_alt.txt";
	// 	int 		fd = open(name, O_RDONLY);
	// 	t_string	line;

	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	free(line);

	// 	close(fd);
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	free(line);

	// 	fd = 345;
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	free(line);
	// }

	// {
	// 		t_string	name = "quijote.txt";
	// 		int 		fd = open(name, O_RDONLY);
	// 		t_string	line;

	// 		// Read an entire file
	// 		while ((line = get_next_line(fd)) != NULL)
	// 		{
	// 			printf("%s", line);
	// 			free(line);
	// 		}
	// 		printf("the end :)");

	// 		// read a single one
	// 		// line = get_next_line(fd);
	// 		// printf("%s", line);
	// }

	// STDIN
	// {
	// 	int fd;
	// 	char *line;
	// 	fd = fileno(stdin);

	// 	while ((line = get_next_line(fd)) != NULL)
	// 	{
	// 		printf("%s", line);
	// 		free(line);

	// 	}
	// 	return (0);
	// }
// }
