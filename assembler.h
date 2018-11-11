
#include "libft/libft.h"

typedef struct s_form
{
	char *name;
	char *comment;
	int is_n;
	int is_c;
	int hash;
	int i;
	int fd;
}				t_form;



char *ft_get_name(t_form *assm, char *line, int k);
char *ft_get_comment(t_form *assm, char *line, int k);
void ft_reader(t_form *assm, char *line);
int ft_check_space(char *line, int i, t_form *assm, char *param);
void ft_zero(t_form *assm);
void ft_error(char *param);
char *ft_name_next(t_form *assm, char *line, int k);
char *ft_comment_next(t_form *assm, char *line, int k);