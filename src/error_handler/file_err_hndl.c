#include "vm.h"

void	ft_error(char *file, char *err_mess)
{
	ft_putstr("Error: ");
	ft_putstr(file);
	ft_putchar(' ');
	ft_putstr(err_mess);
	ft_putchar('\n');
	exit(-1);
}
