/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:15 by facosta           #+#    #+#             */
/*   Updated: 2025/01/03 20:13:21 by facosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlcpy(char *dest, char *src, size_t size);

static char	*gnl_strdup(char *str)
{
	size_t	len;
	char	*res;

	len = gnl_strlen((char *)str) + 1;
	res = malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	gnl_strlcpy(res, str, len + 1);
	return (res);
}

char	*gnl_strchr(char *s, int c)
{
	char	*str2;

	if (!s)
		return (0);
	if (c < 0 || c > 255)
		return ((char *)s);
	str2 = (char *)s;
	while (*str2 != c && *str2)
		str2++;
	if (*str2 == c)
		return (str2);
	return (0);
}

size_t	gnl_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = gnl_strlen((char *)src);
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

// cambia el contenido de s1 por un string nuevo que es s1+s2
// Si en algun momento falla algo, el string s1 no se toca y ya
void	gnl_strjoin(string *p_s1, string s2)
{
	string	res;
	size_t	len1;
	size_t	len2;

	// if (!s1 && !s2)
	// 	return (gnl_strdup(""));
	// if (s1 && !s2)
	// 	return (gnl_strdup(s1));
	// if (!s1 && s2)
	// 	return (gnl_strdup(s2));
	if (!p_s1 || !(*p_s1) || !s2)
		return ;
	len1 = gnl_strlen(*p_s1);
	len2 = gnl_strlen(s2);
	res = malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return ;
	gnl_strlcpy(res, *p_s1, len1 + 1); // copy from the beggining of res, all s1
	free(*p_s1);  // This frees the memory in the line pointer received by arg
	// with the return value, we're not replacing the memory address of line
	// to the result of joining these 2 strings together
	gnl_strlcpy(res + len1, s2, len2 + 1);  // starting at the end of the s1 in res, copy all of s2
	*p_s1 = res;
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;

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
