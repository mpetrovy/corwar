
#include "libft/libft.h"

typedef struct s_form
{
	char *name;
	char *comment;
	int is_n;
	int is_c;
	int hash;
	int i;
}				t_form;



void ft_get_name(t_form *assm, char *line);
void ft_get_comment(t_form *assm, char *line);
void ft_reader(t_form *assm, int fd, char *line);
int ft_check_space(char *line, int i, t_form *assm, char *param);
void ft_zero(t_form *assm);
void ft_error(char *param);