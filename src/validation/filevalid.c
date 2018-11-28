#include "vm.h"

int 	ft_valid_file(char *file)
{
	char	*str;

	str = file;
	if (ft_strcmp(str, "-v") && ft_strcmp(str, "-n") && ft_strcmp(str, "-dump"))
	{
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
		return (0);
	}
	return (0);
}