/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 18:15:42 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/04 18:17:15 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>//delete after all
# define READ_SIZE 4097

typedef struct 			s_carr
{
	unsigned int		cur_pos;
	unsigned int		carry;
	unsigned int		ofset;
	int					index;
	short				player;
	int 				car_index;
	unsigned int		plr_num;
	int					args[3];
	unsigned int		reg[REG_NUMBER];
	unsigned int		alive;
	int					command;
	int					cycles;
	short				working;
}						t_carr;

typedef struct 			s_plr
{
	char				*file_name;
	int 				file_size;
	int					lifes;
	t_header			head;
	unsigned char		*code;
	unsigned int 		plr_pos;
	unsigned int		n_numb;
}						t_plr;

typedef struct 			s_carlist
{
	t_carr				carr;
	struct s_carlist	*next;
}						t_carlist;

typedef struct			s_registers
{
	unsigned int		reg1;
	unsigned int		reg2;
	unsigned int		reg3;
}						t_registers;

typedef struct			s_intstruct
{
	short				reg1;
	short				reg2;
	short				reg3;
}						t_intstruct;

typedef struct			s_codage
{
	unsigned char		nbr;
	int					arg;
}						t_codage;

typedef	struct			s_targparse
{
	int					ac;
	int					p;
}						t_targparse;

typedef struct 			s_env
{
	int 				cycle_to_die;
	int					cur_cycle;
	int					dump;
	int					flag_num; 
	int					winner;
	int					checks;
	int					lives;
	int					carriage_index;
	t_carlist			*head;
	unsigned char		fild[MEM_SIZE];
	t_plr				plrs[5];
	short				plr_numb;
	t_values			funcs[17];
}						t_env;

typedef void			(*t_hndl)(t_env*, t_carr*);

/*
**	vmrdcor/rdcor.c
*/
void					ft_read_cor(t_env *e, int ac);
/*
**	carriage.c
*/
void					ft_init_carriage(t_env *e);
/*
**	carrun.c
*/
void					ft_check_codage(t_env *e, t_carr *car, int *i, t_codage *cod);
void					ft_carriage_run(t_env *e);
/*
**	validation/filevalid.c
*/
int 					ft_valid_file(char *file);
/*
**	error_handler/file_err_hndl.c
*/
void					ft_error(char *file, char *err_mess);
/*
**	flag_debug.c
*/
void					ft_check_cycle(t_env *e, short *live);
void					ft_check_killed_carriage(t_env *e);
void					ft_set_handlers(t_hndl *func);
int 					ft_check_pos(int pos);
void					ft_show_for_debug(t_env *e);
/*
**	parsing.c
*/
void					ft_parse_input(t_env *e, int ac, char **av);
/*
**	initialization.c
*/
void					ft_fill_env(t_env *e, int i, int p);
/*
** move_carriage.c
*/
void 					ft_carstep(t_env *e, int *cycles);
/*
** function_handlers
*/
void					ft_check_killed_carriage(t_env *e);
void					ft_update(t_env *e);
typedef unsigned int 	(*t_get)(t_env*, t_carr*, int*);

void					ft_adv_show(t_env *e, t_carr *car, unsigned int step);
unsigned int			ft_get_value(t_env *e, int cur_pos, int label);
void					ft_set_f(t_get *f);
void					ft_live_hndl(t_env *e, t_carr *car);
void					ft_ld_hndl(t_env *e, t_carr *carr);
void					ft_st_hndl(t_env *e, t_carr *car);
void					ft_add_hndl(t_env *e, t_carr *car);
void					ft_sub_hndl(t_env *e, t_carr *car);
void					ft_and_hndl(t_env *e, t_carr *car);
void					ft_or_hndl(t_env *e, t_carr *car);
void					ft_xor_hndl(t_env *e, t_carr *car);
void					ft_zjump_hndl(t_env *e, t_carr *car);
void					ft_ldi_hndl(t_env *e, t_carr *car);
void					ft_sti_hndl(t_env *e, t_carr *car);
void					ft_fork_hndl(t_env *e, t_carr *car);
void					ft_lld_hndl(t_env *e, t_carr *car);
void					ft_lldi_hndl(t_env *e, t_carr *car);
void					ft_lfork_hndl(t_env *e, t_carr *car);
void					ft_aff_hndl(t_env *e, t_carr *car);

#endif
