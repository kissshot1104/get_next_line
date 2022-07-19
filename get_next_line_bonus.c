/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeapark <jeapark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:06:49 by jeapark           #+#    #+#             */
/*   Updated: 2022/07/19 20:00:48 by jeapark          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == 0)
		return ((char *)(s + i));
	return (0);
}

static char	*ft_cut_line2(char **buf_bak, char **line, char *pos)
{
	char	*tmp;

	*line = ft_substr(*buf_bak, 0, (pos - *buf_bak) + 1);
	if (!(*line))
	{
		free(*buf_bak);
		*buf_bak = 0;
		return (0);
	}
	tmp = ft_substr(pos, 1, ft_strlen(pos + 1));
	if (!tmp)
	{
		free(*line);
		*line = 0;
		return (0);
	}
	free(*buf_bak);
	*buf_bak = tmp;
	return (*line);
}

static char	*ft_cut_line(char **buf_bak)
{
	char	*pos;
	char	*line;

	if (*buf_bak == 0)
	{
		return (0);
	}
	if (*buf_bak[0] == 0)
	{
		free(*buf_bak);
		*buf_bak = 0;
		return (0);
	}
	pos = ft_strchr(*buf_bak, '\n');
	if (!pos)
	{
		line = *buf_bak;
		*buf_bak = 0;
		return (line);
	}
	return (ft_cut_line2(buf_bak, &line, pos));
}

char	*get_next_line(int fd)
{
	static char	*buf_bak[OPEN_MAX];
	char		read_buf[BUFFER_SIZE + 1];
	char		*tmp;
	size_t		read_size;

	if (fd < 0 || OPEN_MAX < fd || BUFFER_SIZE <= 0 || \
	read(fd, read_buf, 0) == -1)
		return (0);
	if (ft_strchr(buf_bak[fd], '\n'))
		return (ft_cut_line(&buf_bak[fd]));
	read_size = read(fd, read_buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		tmp = 0;
		read_buf[read_size] = 0;
		tmp = buf_bak[fd];
		buf_bak[fd] = ft_strjoin(buf_bak[fd], read_buf);
		if (tmp)
			free(tmp);
		if (ft_strchr(buf_bak[fd], '\n'))
			return (ft_cut_line(&buf_bak[fd]));
		read_size = read(fd, read_buf, BUFFER_SIZE);
	}
	return (ft_cut_line(&buf_bak[fd]));
}
