#include "vm.h"

int 	ft_valid_file(char *file)
{
	char	*str;

	str = file;
	while (*file)
	{
		if (*file == '.')
		{
			if (!ft_strcmp(file, ".cor"))
				return (1);
			else
				ft_error(str, "file has not valid format");
		}
		file++;
	}
	ft_error(str, "file not valid");
	return (0);
}