/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:15 by facosta           #+#    #+#             */
/*   Updated: 2025/01/08 11:41:34 by facosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlcpy(t_string dest, t_string src, size_t size);

static t_string	gnl_strdup(t_string str)
{
	size_t		len;
	t_string	res;

	len = gnl_strlen(str) + 1;
	res = malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	gnl_strlcpy(res, str, len + 1);
	return (res);
}

t_string	gnl_strchr(t_string s, int c)
{
	t_string	str2;

	if (!s)
		return (0);
	if (c < 0 || c > 255)
		return ((t_string) s);
	str2 = (t_string) s;
	while (*str2 != c && *str2)
		str2++;
	if (*str2 == c)
		return (str2);
	return (0);
}

size_t	gnl_strlcpy(t_string dest, t_string src, size_t size)
{
	size_t	i;
	size_t	len;

	len = gnl_strlen((t_string) src);
	i = 0;
	if (size == 0)
		return (len);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	return (len);
}

// Exchange the contents of the string s1(passed by ref) to s1+s2.
// If anything goes wrong, just don't touch s1
// DETAILS: we do free(*p_s1) to liberate the memory in the line pointer
// received by arg, to make the ref to line point to a different string now
void	gnl_strjoin(t_string *p_s1, t_string s2)
{
	t_string	res;
	size_t		len1;
	size_t		len2;

	if (!p_s1 || !(*p_s1) || !s2)
		return ;
	len1 = gnl_strlen(*p_s1);
	len2 = gnl_strlen(s2);
	res = malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return ;
	gnl_strlcpy(res, *p_s1, len1 + 1);
	free(*p_s1);
	gnl_strlcpy(res + len1, s2, len2 + 1);
	*p_s1 = res;
}

t_string	gnl_substr(t_string s, unsigned int start, size_t len)
{
	t_string	res;
	size_t		s_len;

	s_len = gnl_strlen(s);
	if (!s)
		return (NULL);
	if (start >= s_len)
		return (gnl_strdup(""));
	if (len > s_len - start)
		return (gnl_strdup(s + start));
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	gnl_strlcpy(res, s + start, len);
	res[len] = '\0';
	return (res);
}
