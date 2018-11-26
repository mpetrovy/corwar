// gcc -g -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
//gcc -o test main.o -I libft/includes -L libft/ -lft

#include "assembler.h"

// int main()//int argc, char **argv)
// {
// 	char *line;
// 	t_form assm;

// 	line = NULL;
// 	// if (argc != 2 && ft_strstr(argv[1], ".s"))
// 	// 	return (0);
// 	assm.fd = open("123", O_RDONLY);
// 	if (assm.fd <= -1)
// 		return (0);
// 	ft_zero(&assm);
// 	ft_reader(&assm, line);
// }

int main(int argc, char **argv)
{
	char *line;
	t_form assm;

	line = NULL;
	if (argc != 2 || !ft_strstr(argv[1], ".s"))
	 	ft_error("file");
	assm.fd = open(argv[1], O_RDONLY);
	if (assm.fd <= -1)
		ft_error("file");
	ft_zero(&assm);
	ft_reader(&assm, line);
}

void ft_zero(t_form *assm)
{
	assm->name = NULL;
	assm->comment = NULL;
	assm->is_n = 0;
	assm->is_c = 0;
	assm->is_cmd = 0;
	assm->is_com = 1;
	assm->hash = 0;
	assm->i = 0;
}

void ft_reader(t_form *assm, char *line)
{
	int i;

	i = 0;
	 while (get_next_line(assm->fd, &line) > 0)
	 {
	 	if (i == 0 && line == NULL)
	 		exit(0);
	 	else if (ft_strstr(line, ".name"))
	 		line = ft_get_name(assm, line, 0);
	 	else if (ft_strstr(line, ".comment"))
	 	 	line = ft_get_comment(assm, line, 0);
	 	else if ((assm->i_cmd = ft_find_command(assm, line)) != 17 || assm->is_l == 1)
	 		line = ft_get_command(assm, line, 0, NULL);
	 	else if (ft_space_line(line) == 0)
	 		ft_error("line");
	 	i++;
		if (line != NULL)
	 		ft_strdel(&line);
	 }
	 if (assm->is_c != 1 || assm->is_n != 1 || assm->is_cmd == 0)
			ft_error("file");
}


int ft_space_line(char *line)
{
	int i;
	int hash;

	hash = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '#')
			hash = 1;
		if (line[i] != ' ' && line[i] != '\t' && hash == 0)
			return (0);
		i++;
	}
	return (1);
}

char *ft_name_next(t_form *assm, char *line, int k)
{
	char *str;
	int l;

	l = 0;
	assm->i = 0;
	str = ft_strsub(line, k, ft_strlen(line) - k);
	ft_strdel(&line);
	if (!(get_next_line(assm->fd, &line)))
			ft_error("name");
	while (ft_strchr(line, '"') == 0)
	{
		str = ft_strjoin(str, line);
		ft_strdel(&line);
		if (!(get_next_line(assm->fd, &line)))
			ft_error("name");
	}
	while (line[assm->i] != '"')
		assm->i++;
	str = ft_strjoin(str, line);
	while(str[l] != '"')
		l++;
	assm->name = ft_strsub(str, 0, l);
	ft_strdel(&str);
	return (line);
}

void ft_error(char *param)
{
	ft_putstr("bad ");
	ft_putendl(param);
	exit(0);
}

int ft_check_space(char *line, int nc, t_form *assm, char *param)
{
	if (nc == 0)
	{
		if (line[assm->i] != ' ' && line[assm->i] != '\t')
			ft_error(param);
		assm->i++;
	}
	if (nc == 1)
	{
		if (line[assm->i] == '#' || line[assm->i] == ';')
			assm->hash = 1;
		if (line[assm->i] != ' ' && line[assm->i] != '\t' && assm->hash == 0)
			ft_error(param);
		assm->i++;
	}
	return(assm->i);
}

char *ft_get_name(t_form *assm, char *line, int k)
{
	assm->i = 0;
	while (line[assm->i] == ' ' || line[assm->i] == '\t')
		assm->i = ft_check_space(line, assm->is_n, assm, "name");
	if (ft_strncmp(&line[assm->i], ".name", 5) != 0)
		ft_error("name");
	assm->i = assm->i + 5;
	while (line[assm->i] != '"')
		assm->i = ft_check_space(line, assm->is_n, assm, "name");
	k = assm->i;
	assm->i++;
	while (line[assm->i] != '"' && line[assm->i] != '\0')
		assm->i++;
	if (line[assm->i] == '"')
		assm->name = ft_strsub(line, k + 1, assm->i - k - 1);
	else
		line = ft_name_next(assm, line, k + 1);
	assm->is_n++;
	if (ft_strlen(assm->name) > 128)
		ft_error("name");
	assm->i++;
	while (line[assm->i] != '\0')
		assm->i = ft_check_space(line, assm->is_n, assm, "name");
	assm->hash = 0;
	return (line);
}

char *ft_get_comment(t_form *assm, char* line, int k)
{
	assm->i = 0;
	while (line[assm->i] == ' ' || line[assm->i] == '\t')
		assm->i = ft_check_space(line, assm->is_n, assm, "comment");
	if (ft_strncmp(&line[assm->i], ".comment", 8) != 0)
		ft_error("comment");
	assm->i = assm->i + 8;
	while (line[assm->i] != '"')
		assm->i = ft_check_space(line, assm->is_c, assm, "comment");
	k = assm->i;
	assm->i++;
	while (line[assm->i] != '"' && line[assm->i] != '\0')
		assm->i++;
	if (line[assm->i] == '"')
		assm->comment = ft_strsub(line, k + 1, assm->i - k - 1);
	else
		line = ft_comment_next(assm, line, k + 1);
	assm->is_c++;
	if (ft_strlen(assm->comment) > 2048)
		ft_error("comment");
	assm->i++;
	while (line[assm->i] != '\0')
		assm->i = ft_check_space(line, assm->is_n, assm, "comment");
	assm->hash = 0;
	return (line);
}

char *ft_comment_next(t_form *assm, char *line, int k)
{
	char *str;
	int l;

	l = 0;
	assm->i = 0;
	str = ft_strsub(line, k, ft_strlen(line) - k);
	ft_strdel(&line);
	if (!(get_next_line(assm->fd, &line)))
			ft_error("comment");
	while (ft_strchr(line, '"') == 0)
	{
		str = ft_strjoin(str, line);
			ft_strdel(&line);
		if (!(get_next_line(assm->fd, &line)))
			ft_error("comment");
	}
	while (line[assm->i] != '"')
		assm->i++;
	str = ft_strjoin(str, line);
	while(str[l] != '"')
		l++;
	assm->comment = ft_strsub(str, 0, l);
	ft_strdel(&str);
	return (line);
}

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, 0, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, 1, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, 1, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, 1, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, 0, 1, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 1, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0 ,0},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 1, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"fork", 1, {T_DIR}, 12, 800, 0, 1, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 1, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"lfork", 1, {T_DIR}, 15, 1000, 0, 1, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{"aff", 1, {T_REG}, 16, 2, 1, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0},
	{0, 0, {0}, 0, 0, 0, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0}
};

int ft_find_command(t_form *assm, char *line)
{
	int i;
	int j;
	int k;

	assm->is_l = 0;
	i = 0;
	j = ft_find_label(assm, line);
	while (i < 16)
	{
		if (ft_strstr(line + j, op_tab[i].name))
		{	
			while (line[j] == ' ' || line[j] == '\t')
				j++;
			if (line[j] == '#')
				return (17);
			k = j;
			while (line[j] != ' ' && line[j] != '\t')
				j++;
			if (ft_strncmp(line + k, op_tab[i]. name, j - k) == 0)
				return (i);
			j = k;
		}
		i++;
	}
	return (17);
}

int ft_find_label(t_form *assm, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != ':' && line[i] != '#' && line[i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, line[i]))
			i++;
		else
			return (0);
	}
	if (line[i] == ':')
	{
		assm->is_l = 1;
		return (i + 1);
	}
	return (0);
}

char *ft_get_command(t_form *assm, char *line, int i, char *labtmp)
{
	if (assm->is_l == 1)
		labtmp = ft_label_valid(assm, &i, line);
	while (ft_find_command(assm, line) == 17)
	{	
		i = 0;
		ft_strdel(&line);
		if (!(get_next_line(assm->fd, &line)))
		{
			line = NULL;
			assm->is_com = 0;
			break ;
		}
		if (ft_find_label(assm, line) >= 1)
		{
			if (labtmp != NULL)
				ft_strdel(&labtmp);
			labtmp = ft_label_valid(assm, &i, line);
		}
		else if (ft_find_command(assm, line) == 17 && ft_space_line(line) == 0)
			ft_error("line");
	}
	if (assm->is_com != 0)
		ft_add_command(assm, line, i, labtmp);
	return (line);	
}

void ft_add_command(t_form *assm, char *line, int i, char *labtmp)
{
	int k;
	t_op *ptr;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	k = i;
	while (line[i] != ' ' && line[i] != '\t')
		i++;
	if (!assm->com)
	{
		assm->com = ft_memalloc(sizeof(t_op));
		*assm->com = NULL;
	}
	ptr = ft_memalloc(sizeof(t_op));
	ptr->name = ft_strsub(line, k, i - k);
	ptr->argc = op_tab[assm->i_cmd].argc;
	ptr->opcode = op_tab[assm->i_cmd].opcode;
	ptr->labelsize = op_tab[assm->i_cmd].labelsize;
	if (assm->is_l == 1)
		ptr->label = ft_strdup(labtmp);
	else
		ptr->label = NULL;
	ft_arguments(ptr, line + i, assm->i_cmd);
	ptr->next = (*assm->com);
	*assm->com = ptr;
	assm->is_cmd++;
}

void ft_arguments(t_op *ptr, char *line, int com_num)
{
	char **args;

	args = ft_get_arguments(ptr, line);
	
	ft_arg_validate(args, ptr, 0, com_num);
}

void ft_arg_validate(char **args, t_op *ptr, int i, int cnum)
{
	int tmp[3] = {0, 0, 0};

	while (args[i])
	{
		if (args[i][0] == 'r' && ft_atoi(&args[i][1]) >= 1 && ft_atoi(&args[i][1]) <= 16)
			tmp[i] = T_REG;
		else if (args[i][0] == '%' && (args[i][1] == ':' || \
		args[i][1] == '-' || ft_isdigit(args[i][1])))
			tmp[i] = T_DIR;
		else if (ft_isdigit(args[i][0]) || (args[i][1] == '-' && ft_isdigit(args[i][1])) \
		|| (args[i][0] == ':'))
			tmp[i] = T_IND;
		else
			tmp[i] = 42;
		i++;
	}
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == 42)
			ft_error("argument");
		i++;
	}
	ft_parsing_arg(tmp, args, ptr, cnum);
}

void	ft_parsing_arg(int *tmp, char **args, t_op *ptr, int i)
{
	int j;

	j = 0;
	while (args[j])
	{
		if (tmp[j] == T_REG && op_tab[i].args[j] % 2 != 0 )
			ft_REG(args[j], j, ptr);
		else if (tmp[j] == T_DIR && op_tab[i].args[j] != 1 && op_tab[i].args[j] != 4 && op_tab[i].args[j] != 5 )
			ft_DIR(args[j], j, ptr, 1);
		else if (tmp[j] == T_IND && op_tab[i].args[j] != 1 && op_tab[i].args[j] != 2)
			ft_IND(args[j], j, ptr);
		else
			ft_error("argument");
		j++;
	}	
}

void ft_REG(char *args, int i, t_op *ptr)
{
	int k;
	int value;

	k = 1;
	if (args[0] != 'r')
		ft_error("argument");
	while (args[k] != '\0')
	{
		if (ft_isdigit(args[k]) == 0)
			ft_error("argument");
		k++;
	}
	value = ft_atoi(args + 1);
	if (value < 1 || value > 16)
		ft_error("argument");
	ptr->arg[i].type = 1;
	ptr->arg[i].val = value;
	ptr->arg[i].labe = NULL;
}

void ft_DIR(char *args, int i, t_op *ptr, int k)
{
	long int value;
	
	if (args[0] != '%')
		ft_error("argument");
	if (args[1] == ':')
		ft_label_arg(args, i, ptr, 1);
	else
	{
		if (args[1] == '-')
			k = 2;
		while (args[k] != '\0')
		{
			if (ft_isdigit(args[k]) == 0)
				ft_error("argument");
			k++;
		}
		value = ft_atoi(args + 1);
		if (value > 4294967295)
			ft_error("argument");
		ptr->arg[i].type = DIR_SIZE;
		ptr->arg[i].val = value;
		ptr->arg[i].labe = NULL;
	}
}

void ft_label_arg(char *args, int i, t_op *ptr, int k)
{
	char *str;
	int j;

	j = 0;
	while (args[j] != ':')
		j++;
	str = ft_strdup(args + j + 1);
	j = 0;
	while (str[j] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, str[j]) == 0)
			ft_error("argument label");
		j++;
	}
	ptr->arg[i].labe = ft_strdup(str);
	if (k == 1)
	{	
		ptr->arg[i].type = op_tab[i].labelsize;
		ptr->arg[i].val = 42;
	}
	ft_strdel(&str);
}

void ft_IND(char *args, int i, t_op *ptr)
{
	int k;
	int value;

	value = 0;	
	k = 0;
	if (args[0] == ':')
		ft_label_arg(args, i, ptr, 0);
	else
	{
		if (args[0] == '-')
			k = 1;
		while (args[k] != '\0')
		{
			if (ft_isdigit(args[k]) == 0)
				ft_error("argument");
			k++;
		}
		value = ft_atoi(args);
		ptr->arg[i].labe = NULL;
	}
	ptr->arg[i].type = IND_SIZE;
	ptr->arg[i].val = value;
}

char **ft_get_arguments(t_op *ptr, char *line)
{
	int i;
	char *arg;
	char **argument;

	i = 0;
	while (line[i] != '#' && line[i] != ';' && line[i] != '\0')
		i++;
	arg = ft_strsub(line, 0, i);
	argument = ft_strsplit(arg, ',');
	ft_strdel(&arg);
	if (argument[ptr->argc] != NULL)
		ft_error("argument");
	i = 0;
	while (argument[i])
	{
		arg = ft_strtrim(argument[i]);
		ft_strdel(&argument[i]);
		argument[i] = ft_strdup(arg);
		ft_strdel(&arg);
		i++;
	}
	return (argument);
}

char *ft_label_valid(t_form *assm, int *i, char *line)
{
	int k;
	char *lab;
	int j;

	assm->hash = 0;
	while (line[*i] == ' ' || line[*i] == '\t')
		*i = *i + 1;
	k = *i;
	while (line[*i] != ':')
		*i = *i + 1;
	*i = *i + 1;
	if (ft_find_command(assm, line) == 17)
	{
		j = *i;
		while (line[j] != '\0')
		{
			if (line[j] == '#')
				assm->hash = 1;
			if ((line[j] != ' ' && line[j] != '\t') && assm->hash == 0)
				ft_error("label");
			j++;
		}
	}
	lab = ft_strsub(line, k, *i - k - 1);
	return (lab);
}
