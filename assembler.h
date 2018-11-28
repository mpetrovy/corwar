/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:11 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:26:12 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H
# define MAX 4294967295
# include "libft/libft.h"
# include "op.h"

typedef struct	s_l
{
	char		*lab;
	struct s_l	*next;
}				t_l;

typedef	struct	s_ar
{
	int			type;
	long int	val;
	char		*labe;
	char		*bin;
}				t_ar;

typedef struct	s_op
{
	char		*name;
	int			argc;
	int			args[3];
	int			hex;
	int			labelsize;
	t_ar		arg[3];
	t_l			**label;
	int			bytes;
	int			codage;
	int			cod;
	int			lc;
	struct s_op *next;
}				t_op;

typedef struct	s_form
{
	char		*name;
	char		*comment;
	int			is_n;
	int			is_c;
	int			is_l;
	int			is_com;
	int			is_cmd;
	int			hash;
	int			i;
	int			fd;
	int			i_cmd;
	int			nbr_bytes;
	int			check;
	t_l			**labels;
	t_op		**com;
}				t_form;

t_op			g_op_tab[17];

char			*ft_get_name(t_form *assm, char *line, int k);
char			*ft_get_comment(t_form *assm, char *line, int k);
void			ft_reader(t_form *assm, char *line);
int				ft_check_space(char *line, int i, t_form *assm, char *param);
void			ft_zero(t_form *assm);
void			ft_error(char *param);
char			*ft_name_next(t_form *assm, char *line, int k);
char			*ft_comment_next(t_form *assm, char *line, int k);
int				ft_find_command(t_form *assm, char *line);
char			*ft_get_command(t_form *assm, char *line, int i, char *labtmp);
void			ft_add_command(t_form *assm, char *line, int i);
char			*ft_label_valid(t_form *assm, int *i, char *line);
int				ft_find_label(t_form *assm, char *line);
int				ft_space_line(char *line);
void			ft_arguments(t_op *ptr, char *line, int com_num);
char			**ft_get_arguments(t_op *ptr, char *line);
void			ft_arg_validate(char **args, t_op *ptr, int i, int cnum);
void			ft_parsing_arg(int *tmp, char **arg, t_op *ptr, int i);
void			ft_reg(char *args, int i, t_op *ptr);
void			ft_dir(char *args, int i, t_op *ptr, int k);
void			ft_ind(char *args, int i, t_op *ptr);
void			ft_label_arg(char *args, int i, t_op *ptr, int k);
int				ft_tabs(t_form *assm, char *str, int i, int *k);
void			ft_com_init(t_op *ptr, t_form *assm);
void			ft_bytes(t_op *ptr);
void			ft_set_code(t_op *ptr, int i);
int				ft_atoi_base(const char *str, int str_base);
int				base(int c, int base);
int				ft_isspace(char const c);
void			ft_set_label(t_form *assm);
void			ft_label_in_list(t_form *assm, t_op *ptr, char *str, \
	int number);
void			ft_write_bit(t_form *assm, int c, int bit, int i);
void			ft_write(t_form *assm, char *fname, unsigned long i);
void			ft_size(t_form *assm);
void			ft_write_comment(t_form *assm);
void			ft_write_command(t_form *assm, int i);
void			ft_add_label(t_form *assm, char *labtmp);
void			ft_label_cpy(t_form *assm, t_op *ptr);
int				ft_check_label_end(t_form *assm, char *str);
void			ft_free(t_form *assm);
void			free_comlist(t_op *head);
void			ft_free_labelist(t_l *head);
char			**ft_trim(char **argument, int i, char *arg);
void			ft_check_label_code(int check, t_op *tmp, t_op *ptr, \
	t_form *assm);
void			ft_check_label(t_op *tmp, t_l *node, t_form *assm, char *str);
void			ft_is_l(t_form *assm, char *line, int *i, char *labtmp);

#endif
