/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: facosta <facosta@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:16:15 by facosta           #+#    #+#             */
/*   Updated: 2025/01/03 01:27:13 by facosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlcpy(char *dest, char *src, size_t size);

static char	*gnl_strdup(char *str)
{
	size_t	len;
	char	*out;

	len = gnl_strlen((char *)str) + 1;
	out = malloc(len * sizeof(char));
	if (!out)
		return (NULL);
	gnl_strlcpy(out, str, len + 1);
	free (str);
	return (out);
}

char	*gnl_strchr(const char *s, int c)
{
	char	*ptr;

	if (!s)
		return (0);
	ptr = (char *) s;
	while (*ptr)
	{
		if (*ptr == c)
			return (ptr);
		ptr++;
	}
	if (*ptr == c)
		return (ptr);
	return (NULL);
}

size_t	gnl_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	if (size)
	{
		i = 0;
		while (src[i] && (i < size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (gnl_strlen(src));
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (gnl_strdup(""));
	if (s1 && !s2)
		return (gnl_strdup(s1));
	if (!s1 && s2)
		return (gnl_strdup(s2));
	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	res = malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return (0);
	gnl_strlcpy(res, s1, len1 + 1); // copy from the beggining of res, all s1
	// free(s1);  // This frees the memory in the line pointer received by arg
	// with the return value, we're not replacing the memory address of line
	// to the result of joining these 2 strings together
	gnl_strlcpy(res + len1, s2, len2 + 1);  // starting at the end of the s1 in res, copy all of s2
	return (res);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	len_snstart;

	if (!s)
		return (NULL);
	if (start >= gnl_strlen(s))
		return (gnl_strdup(""));
	len_snstart = gnl_strlen(s + start);
	if (len > len_snstart)
		len = len_snstart;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	gnl_strlcpy(res, s + start, len + 1);
	return (res);
}
