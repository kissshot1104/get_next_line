
#include "get_next_line.h"

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

	if (!(fd = open("/home/hello/workspace/get_next_line/t.txt", O_RDONLY)))
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

