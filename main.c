// clang -g -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
//clang -o test main.o -I libft/includes -L libft/ -lft

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
	{"live", 1, {T_DIR}, 1, 10, 0, 0, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 0, 0, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 0, 0, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 0, 0, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 0, 0, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, 1, 0, 0, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, 1, 0, 0, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, 1, 0, 0, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, 0, 1, 0, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 1, 0, 0},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 1, 0, 0},
	{"fork", 1, {T_DIR}, 12, 800, 0, 1, 0, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 0, 0, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 1, 0, 0},
	{"lfork", 1, {T_DIR}, 15, 1000, 0, 1, 0, 0},
	{"aff", 1, {T_REG}, 16, 2, 1, 0, 0, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0}
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
	ptr->next = (*assm->com);
	*assm->com = ptr;
	assm->is_cmd++;
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
