#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)&s[i]);
		}
		++i;
	}
	if ((unsigned char)c == s[i])
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	ft_strlcpy(ptr, s1, s1_len + 1);
	free((void *)s1);
	ft_strlcpy(ptr + s1_len, (char *)s2, s2_len + 1);
	return (ptr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_length;

	i = 0;
	src_length = ft_strlen(src);
	while (src[i] != '\0' && dstsize > i + 1)
	{
		dst[i] = src[i];
		++i;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (src_length);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	s1_length;

	s1_length = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * (s1_length + 1));
	if (ptr == 0)
		return (0);
	ft_strlcpy(ptr, s1, s1_length + 1);
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;
	unsigned int	s_length;

	s_length = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	i = 0;
	while (start < s_length && s[start] != '\0' && len > i)
	{
		str[i] = s[start];
		++i;
		++start;
	}
	str[i] = '\0';
	return (str);
}



static	int	cut_new_line(char **buf, char **line)
{
	char	*patrol;
	char	*temp;

	if (!buf || !*buf)
	{
		*line = ft_strdup("");
		return ((*line != 0) ? 0 : -1);
	}
	patrol = ft_strchr(*buf, '\n');
	if (!patrol)
	{
		//개행이 없으면 문자열 주소를 옮겨줌(EOF을 뜻하는거라 생각하면 될듯함)
		*line = *buf;		//line = {a, null}
		*buf = 0;
		return (1);
	}
	if (!(*line = ft_substr(*buf, 0, patrol - *buf)))
		return (-1);
	if (!(temp = ft_substr(patrol + 1, 0, ft_strlen(patrol + 1))))
	{
		free(*line);
		return (-1);
	}
	free(*buf);
	*buf = temp;
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char *storage[_SC_OPEN_MAX];
	char		str_buffer[BUFFER_SIZE + 1];
	size_t		read_size;
	int			return_val;

	if (read(fd, str_buffer, 0) == -1 || !line || BUFFER_SIZE <= 0)	//예외처리
		return (-1);
	if (ft_strchr(storage[fd], '\n'))		//fd에 '\n'가 있는가 없는가에 대해서(맨 처음에는 할당 안됨 그러니 null)
		return (cut_new_line(&storage[fd], line));
	while ((read_size = read(fd, str_buffer, BUFFER_SIZE)) > 0)
	{
		str_buffer[read_size] = 0;
		storage[fd] = ft_strjoin(storage[fd], str_buffer);
		if (ft_strchr(storage[fd], '\n'))
			return (cut_new_line(&storage[fd], line));
	}
	//'\n'을 다 잘라냈거나 없어서 끝이 나는경우에 마지막 이것을 실행
	return_val = cut_new_line(&storage[fd], line);	//storage[fd] = {a, null}, line = 0(할당안됨)
	if (return_val == 1)
		return (0);
	return (return_val);
}

# include<stdio.h>
# include <fcntl.h>

int main() {
	int fd;
	int i;
	int j;
	char *line = 0;
	//char *lineadress[66];

	j = 1;
	printf("\n==========================================\n");
	printf("========= TEST 2 : Empty Lines ===========\n");
	printf("==========================================\n\n");

	if (!(fd = open("/home/hello/workspace/get_next_line/test.txt", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	printf("%d\n" ,fd);
	free(line);
	close(fd);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 59)
		printf("\nRight number of lines\n");
	else if (j != 59)
		printf("\nNot Good - Wrong Number Of Lines\n");
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hello <hello@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:16:28 by hello             #+#    #+#             */
/*   Updated: 2022/07/17 23:43:33 by hello            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

/*#include "get_next_line.h"

static int cut_new_line2(char **buf, char **line, char *patrol)
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
}
*/
