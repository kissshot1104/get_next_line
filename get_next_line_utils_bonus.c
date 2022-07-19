/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeapark <jeapark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:12:40 by jeapark           #+#    #+#             */
/*   Updated: 2022/07/19 20:02:37 by jeapark          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcpy(str + s1_len, (char *)s2, s2_len + 1);
	return (str);
}

char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	char	*alloc;
	size_t	i;

	i = 0;
	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	alloc = (char *)malloc(s1_len + 1);
	if (alloc == 0)
		return (0);
	while (i < s1_len)
	{
		alloc[i] = s1[i];
		i++;
	}
	alloc[i] = 0;
	return (alloc);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	char	*str;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len < start)
		return (ft_strdup(""));
	if (s_len - start < len)
		str = (char *)malloc(s_len - start + 1);
	else
		str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	i = 0;
	while (i < len && s[i + start])
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = 0;
	return (str);
}
