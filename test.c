# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

#  define BUFFER_SIZE 70

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

static int cut_new_line2(char **buf, char **line, char *patrol)
{
	char *tmp;

	if (!(*line = ft_substr(*buf, 0, patrol - *buf)))	//substr
		return (-1);			//null이 할당된것이라면 문제가 발생한것
	//patrol + 1인 이유는 patrol + 1을 함으로써 '\n를 건너띈 주소를 인자로 넘김
	//아마 한번에 읽혀진 문자열에 '\n'가 있는곳마다 잘라서 처리하기위해 사용되는것이라 생각한다.
	if (!(tmp = ft_substr(patrol + 1, 0, ft_strlen(patrol + 1))))//\n까지 잘라서 tmp에 저장함
	{
		free(*line);
		return (-1);
	}
	free(*buf);		//기존 문자열을 할당 해제하고
	*buf = tmp;		//'\n'다음의 문자열들이 모인 buf에 넣어줌
	return (1);
}

static int cut_new_line(char **buf, char **line)
{
	char	*patrol;

	if (!buf || !*buf)//buf가 null일 경우는 에러가 발생했다고 보는것이 타당할듯함
	{
		*line = ft_strdup("");
		if (*line != 0)
			return (0);
		else
			return (-1);
	}
	patrol = ft_strchr(*buf, '\n');		//문자열에서 '\n'가 있는 주소를 구함(잘라내기 위함일듯함)
	if (!patrol)
	{
		//개행이 없으면 문자열 주소를 옮겨줌(EOF즉 문자열의 끝을 만나 프로그램을 정지할 떄 씀)
		*line = *buf;		//*line에 *buf의 문자열의 주소를 넣어줌
		*buf = 0;
		return (1);
	}
	return (cut_new_line2(buf, line, patrol));
}

int	get_next_line(int fd, char **line)
{
	static char *storage[_SC_OPEN_MAX];		//OPEN_MAX 일것이다.
	char		str_buffer[BUFFER_SIZE + 1];
	size_t		read_size;
	int			return_val;

	if (read(fd, str_buffer, 0) == -1 || !line || BUFFER_SIZE <= 0)//예외처리
		return (-1);
	if (ft_strchr(storage[fd], '\n'))					//'\n'이 있으면 실행
		return (cut_new_line(&storage[fd], line));		//만약 한 번 돌고나서 돌았는데
										//"\n\n"이런식으로 연속으로 있는것을 처리하기 위함
										//이것을 안하면 다음것을 그대로 읽어버려서 오류가 발생할수도있음
	while (1)
	{
		read_size = read(fd, str_buffer, BUFFER_SIZE);
		if (read_size <= 0)		//읽기가 끝나거나 에러가 날 시 break ;
			break ;
		str_buffer[read_size] = 0;		//문자열에 끝에 null을 넣기위함
		storage[fd] = ft_strjoin(storage[fd], str_buffer);	//fd에 문자열을 백업을함
		if (ft_strchr(storage[fd], '\n'))
			return (cut_new_line(&storage[fd], line));		//문자열에 \n가 포함되었을 경우 실행(
													//다음것을 불러들일 경우 보통 1이 리턴될듯함
	}
	return_val = cut_new_line(&storage[fd], line);
	if (return_val == -1)
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
