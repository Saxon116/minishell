#include <stdio.h>
#include <limits.h>
#include "libft/libft.h"

int main()
{
	char *line;

	ft_max(1,2);
	ft_printf("$> ");
	while(1)
	{
			if(get_next_line(0, &line))
			{
				ft_printf("newline detected\n");
				return 0;
			}
			free(line);
	}
	return 0;
}
