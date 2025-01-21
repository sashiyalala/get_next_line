/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:15 by facosta           #+#    #+#             */
/*   Updated: 2025/01/21 21:01:07 by facosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(t_string s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	void	*address;
// 	size_t	i;

// 	if (nmemb == 0 || size == 0)
// 		return (NULL);
// 	address = malloc(nmemb * size);
// 	if (!address)
// 		return (NULL);
// 	i = 0;
// 	while (i < (nmemb * size))
// 	{
// 		*((unsigned char *)address + i) = '\0';
// 		++i;
// 	}
// 	return (address);
// }

// Given a starting position, fill with 0 for the following n bytes
void	ft_bzero(void	*p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)p + i) = '\0';
		++i;
	}
}

// Given 2 strings, allocate memory for a new string, the result of concat'ng
// s1 and then, s2.
t_string	ft_strjoin(t_string s1, t_string s2)
{
	t_string	str;
	size_t		len;
	size_t		iter;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (t_string) malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	iter = 0;
	while (s1 && *s1)
	{
		str[iter++] = *s1;
		s1++;
	}
	while (s2 && *s2)
	{
		str[iter++] = *s2;
		s2++;
	}
	str[iter] = '\0';
	return (str);
}

// Given a string, return a pointer pointing the first instance of a given char
// in the string. If not found, return NULL
t_string	ft_strchr(const t_string str, int c)
{
	char		char_c;
	t_string	iter;

	char_c = (char) c;
	iter = (t_string) str;
	if (!str)
		return (NULL);
	while (*iter != '\0')
	{
		if (*iter == char_c)
			return (iter);
		++iter;
	}
	if (char_c == '\0' && *iter == '\0')
		return (iter);
	return (NULL);

}
