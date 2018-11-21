
#include "libft/libft.h"
#include "op.h"


typedef struct s_l
{
	char *lab;
	struct s_l *next;
}				t_l;


typedef struct s_op
{
	char *name;
	int argc;
	int arguments[3];
	int opcode;
	int cycles;
	int codage;
	int labelsize;
	char *label;
	struct s_op *next;
}				t_op;


typedef struct s_form
{
	char *name;
	char *comment;
	int is_n;
	int is_c;
	int is_l;
	int is_com;
	int is_cmd;
	int hash;
	int i;
	int fd;
	int i_cmd;
	char *buf_op;
	t_l **lables;
	t_op **com;
}				t_form;


char *ft_get_name(t_form *assm, char *line, int k);
char *ft_get_comment(t_form *assm, char *line, int k);
void ft_reader(t_form *assm, char *line);
int ft_check_space(char *line, int i, t_form *assm, char *param);
void ft_zero(t_form *assm);
void ft_error(char *param);
char *ft_name_next(t_form *assm, char *line, int k);
char *ft_comment_next(t_form *assm, char *line, int k);
int ft_find_command(t_form *assm, char *line);
char *ft_get_command(t_form *assm, char *line, int i, char *labtmp);
void ft_add_command(t_form *assm, char *line, int i, char *labtmp);
char *ft_label_valid(t_form *assm, int *i, char *line);
int ft_find_label(t_form *assm, char *line);
int ft_space_line(char *line);