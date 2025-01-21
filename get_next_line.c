/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:18 by facosta           #+#    #+#             */
/*   Updated: 2025/01/21 21:04:50 by facosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Given the stockpile, remove everything that is supposed to have gone to the
// resulting line, i.e. everything until a newline or EOF is found
static void	remove_line_from_stockpile(t_string *stockpile)
{
	t_string	p_nl;
	t_string	temp;
	size_t		iter_temp;
	size_t		iter_pile;

	p_nl = ft_strchr(*stockpile, '\n');
	if (!p_nl)
	{
		free(*stockpile);
		*stockpile = NULL;
		return ;
	}
	temp = (char *) malloc((ft_strlen(p_nl)) * sizeof(char));
	iter_temp = 0;
	iter_pile = ft_strlen(*stockpile) - ft_strlen(p_nl) + 1;
	while (iter_pile < ft_strlen(*stockpile))
		temp[iter_temp++] = (*stockpile)[iter_pile++];
	temp[iter_temp] = '\0';
	free(*stockpile);
	*stockpile = temp;
	if (**stockpile == 0)
	{
		free(*stockpile);
		*stockpile = NULL;
	}
}

// Allocate memory and create a new line by copying everything from a given
// stockpile until the first '\n' is found
t_string	get_line_from_stockpile(t_string *stockpile)
{
	t_string	p_nl;
	size_t		len;
	size_t		i;
	t_string	line;

	p_nl = ft_strchr(*stockpile, '\n');
	len = ft_strlen(*stockpile) - ft_strlen(p_nl) + 2;
	line = (char *) malloc(len * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		line[i] = (*stockpile)[i];
		++i;
	}
	line[i] = '\0';
	return (line);
}

// Encapsulation of the process for attempting to read, at max, a length of
// BUFFER_SIZE bytes and concat'ng it at the end of the given stockpile.
// In particular, manage possible errors during call to unistd::read
ssize_t	read_to_buffer(int fd, t_string *stockpile, t_string *buffer)
{
	char	*temp;
	ssize_t	read_bytes;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes < 0 || !buffer)
	{
		free(*stockpile);
		*stockpile = NULL;
		return (-1);
	}
	if (read_bytes == 0)
			return (read_bytes);
	temp = ft_strjoin(*stockpile, *buffer);
	free(*stockpile);
	*stockpile = temp;
	return (read_bytes);
}

// Attempt to fill out a stockpile string by reading, at max, a length of
// BUFFER_SIZE into buffer variable until a '\n' or EOF is found
static t_string	read_nl(int fd, t_string *stockpile)
{
	ssize_t		read_bytes;
	t_string	line;
	t_string	buffer;

	// TODO: Consider allocating buffer here?
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!(ft_strchr(*stockpile, '\n')) && read_bytes > 0)
		read_bytes = read_to_buffer(fd, stockpile, &buffer);
	if (read_bytes < 0)
		return (NULL);
	free(buffer);  // Re. TODO^
	if (ft_strlen(*stockpile) == 0)
		return (NULL);
	line = get_line_from_stockpile(stockpile);
	remove_line_from_stockpile(stockpile);
	return (line);
}

// * Some initial checks
// * allocating 1byte into the resulting line variable, just to initialize it
//   to something
// * if the buffer contains stuff, i.e. a remainder from reading a previous
//   line => put its contents in line
char *	get_next_line(int fd)
{
	static t_string	stockpile;  // line I will paste everything on
	t_string		line;

	if (fd < 0 || fd >= FD_SETSIZE || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_nl(fd, &stockpile);
	return (line);
}
