// clang -g -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
//clang -o test main.o -I libft/includes -L libft/ -lft

#include "assembler.h"

// int main()//int argc, char **argv)
// {
// 	char *line;
// 	t_form assm;
// 	int fd;

// 	line = NULL;
// 	// if (argc != 2 && ft_strstr(argv[1], ".s"))
// 	// 	return (0);
// 	fd = open("123", O_RDONLY);
// 	if (fd <= -1)
// 		return (0);
// 	ft_zero(&assm);
// 	ft_reader(&assm, fd, line);
// }

int main(int argc, char **argv)
{
	char *line;
	t_form assm;
	int fd;

	line = NULL;
	if (argc != 2 || !ft_strstr(argv[1], ".s"))
	 	ft_error("file");
	fd = open(argv[1], O_RDONLY);
	if (fd <= -1)
		ft_error("file");
	ft_zero(&assm);
	ft_reader(&assm, fd, line);
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

void ft_reader(t_form *assm, int fd, char *line)
{
	int i;

	i = 0;
	 while (get_next_line(fd, &line) > 0)
	 {
	 	if (i == 0 && line == NULL)
	 		exit(0);
	 	if (ft_strstr(line, ".name"))
	 		ft_get_name(assm, line);
	 	if (ft_strstr(line, ".comment"))
	 	 	ft_get_comment(assm, line);
	 	i++;
	 	ft_strdel(&line);
	 }
	 if (assm->is_c != 1 || assm->is_n != 1)
			exit(0);
}

void ft_get_name(t_form *assm, char *line)
{
	int k;

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
	while (line[assm->i] != '"')
		assm->i++;
	assm->name = ft_strsub(line, k + 1, assm->i - k - 1);
	assm->is_n++;
	if (ft_strlen(assm->name) > 128)
		ft_error("name");
	assm->i++;
	while (line[assm->i] != '\0')
		assm->i = ft_check_space(line, assm->is_n, assm, "name");
	assm->hash = 0;
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

void ft_get_comment(t_form *assm, char* line)
{
	int k;

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
	while (line[assm->i] != '"')
		assm->i++;
	assm->comment = ft_strsub(line, k + 1, assm->i - k - 1);
	assm->is_c++;
	if (ft_strlen(assm->comment) > 2048)
		ft_error("comment");
	assm->i++;
	while (line[assm->i] != '\0')
		assm->i = ft_check_space(line, assm->is_n, assm, "comment");
	assm->hash = 0;
}

