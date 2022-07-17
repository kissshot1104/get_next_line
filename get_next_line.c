/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hello <hello@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:16:28 by hello             #+#    #+#             */
/*   Updated: 2022/07/18 05:10:49 by hello            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*static int cut_new_line2(char **buf, char **line, char *patrol)
{
	char	*tmp;

	*line = ft_substr(*buf, 0, patrol - *buf);
	if (!(*line))
		return (-1);
	tmp = ft_substr(patrol + 1, 0, ft_strlen(patrol + 1));
	if (!(tmp))
	{
		free(*line);
		return (-1);
	}
	free(*buf);
	*buf = tmp;
	return (1);
}

static int	cut_new_line1(char **buf, char **line)
{
	char	*patrol;

	if (!buf || !*buf)//잘못된 값이 들어온다면 빈문자열 할당 후 반환
	{
		*line = ft_strdup("");
		if (*line != 0)
			return (0);
		else
			return (-1);
	}
	patrol = ft_strchr(*buf, '\n');
	if (!patrol)//마지막출력일 때 호출됨
	{
		//개행이 없으면 문자열 주소를 옮겨줌(EOF을 뜻하는거라생각하면 될듯)
		*line = *buf;
		*buf = 0;
		return (1);
	}
	return (cut_new_line2(buf, line, patrol));
}

int	get_next_line(int fd, char **line)
{
	static char	*storage[_SC_OPEN_MAX];
	char		str_buffer[BUFFER_SIZE + 1];
	size_t		read_size;
	int			return_val;

	if (read(fd, str_buffer, 0) == -1 || !line || BUFFER_SIZE <= 0)	//예외처리
		return (-1);
	if (ft_strchr(storage[fd], '\n'))				//처음 반복때는 절대 실행 안됨
		return (cut_new_line1(&storage[fd], line));//storage는 백업, line은 출력
	read_size = read(fd, str_buffer, BUFFER_SIZE);
	while (read_size > 0)
	{
		str_buffer[read_size] = 0;
		storage[fd] = ft_strjoin(storage[fd], str_buffer);
		if (ft_strchr(storage[fd], '\n'))
			return (cut_new_line1(&storage[fd], line));
		read_size = read(fd, str_buffer, BUFFER_SIZE);
	}
	//'\n'을 다 잘라냈거나 없어서 끝이 나는경우에 마지막 이것을 실행
	return_val = cut_new_line1(&storage[fd], line);
	if (return_val == 1)
		return (0);
	return (return_val);
}*/
static int	ft_cut_line2(char **buf, char **line, char *pos)
{
	char	*tmp;

	*line = ft_substr(*buf, 0, pos - *buf);
	if (!(*line))
		return (-1);
	tmp = ft_substr(pos, 1, ft_strlen(pos + 1));
	if (!tmp)
	{
		free(*line);
		*line = 0;
		return (-1);
	}
	free(*buf);
	*buf = tmp;
	return (1);
}

static int	ft_cut_line(char **buf_bak, char **line)
{
	char	*pos;

	if (!buf_bak || !(*buf_bak))
	{
		*line = ft_strdup("");
		if (!(*line))
			return (-1);
		return (0);
	}
	pos = ft_strchr(*buf_bak, '\n');
	if (!pos)//어차피 맨 마지막에 들어올놈이니 return 0
	{
		*line = *buf_bak;
		*buf_bak = 0;
		return (0);
	}
	return (ft_cut_line2(buf_bak, line, pos));
}

int	get_next_line(int fd, char **line)
{
	static char	*buf_bak[_SC_OPEN_MAX];
	char		read_buf[BUFFER_SIZE + 1];
	size_t		read_size;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, read_buf, 0) == -1)
		return (-1);
	if (ft_strchr(buf_bak[fd], '\n'))
		return (ft_cut_line(&buf_bak[fd], line));
	read_size = read(fd, read_buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		read_buf[read_size] = 0;
		buf_bak[fd] = ft_strjoin(buf_bak[fd], read_buf);
		if (ft_strchr(buf_bak[fd], '\n'))
			return (ft_cut_line(&buf_bak[fd], line));
		read_size = read(fd, read_buf, BUFFER_SIZE);
	}
	return (ft_cut_line(&buf_bak[fd], line));
}

