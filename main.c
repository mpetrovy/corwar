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
	 	if (ft_strstr(line, ".name"))
	 		line = ft_get_name(assm, line, 0);
	 	if (ft_strstr(line, ".comment"))
	 	 	line = ft_get_comment(assm, line, 0);
	 	i++;
		if (line != NULL)
	 		ft_strdel(&line);
	 }
	 if (assm->is_c != 1 || assm->is_n != 1)
			ft_error("file");
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
		if (line[assm->i] == '#')
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
