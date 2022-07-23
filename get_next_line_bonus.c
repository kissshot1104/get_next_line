/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeapark <jeapark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:06:49 by jeapark           #+#    #+#             */
/*   Updated: 2022/07/23 15:20:32 by jeapark          ###   ########seoul.kr  */
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

/*
	@param
		(in)	buf_bak	"자를 문자열이 들어있는 변수"
		(out)	line	"출력하기 위해 잘라낸 문자열이 들어가는 변수"
		(out)	pos		"buf_bak문자열 내의 잘라낼 기준이 되는 문자'\n'의 위치를 나타내는 변수"
	
	@return
		지정된 문자를 기준으로 잘라내 출력할 문자열이 담긴 주소

	@detail
		buf_bak의 문자열에서 첫번 째 개행 pos까지의 문자를 line 에 할당한다.
		그리고 자르고 남은 문자는 tmp에 할당한 후 기존의 buf_bak를 할당 해제하고 아까 잘라내고 남은 문자열을 할당한 tmp를 buf_bak에 집어넣는다.
*/

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
/*
	@param
		(in)	buf_bak	"자를 문자열이 들어있는 변수"

	@return
		지정된 문자를 기준으로 잘라내 출력할 문자열이 담긴 주소
	
	@detail
		해당 주소가 있는지 그리고 빈문자열이 있는지 검사 후 문자열에 \n가 있는지 없는지 검사를 한다.
		없다면 마지막 라인이지만 마지막에 \n가 없는것으로 간주한다. 하지만 개행 '\n'이 있다면
		검사를 한 후 잘라내기 위해 ft_cut_line2()함수를 호출한다.
		
*/
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

/*
	@param 
		(in) fd	"열려있는 파일디스크립터"

	@return
		할당된 문자열이 담긴 주소

	#detail
		해당 함수가 실행되기 적절한지 검사 후 문자를 BUFFER_SIZE만큼 읽어들인다
		그리고 그 문자열 안에 '\n'가 있다면 주소 처음부터 해당 문자'\n'가 있는 문자열까지
		자른다. 하지만 자를 문자'\n'이 보이지않는다면 보일때까지 읽어들인다.
*/
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
