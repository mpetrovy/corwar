/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:11:08 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:11:09 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		main(int argc, char **argv)
{
	char	*line;
	t_form	assm;

	line = NULL;
	if (argc != 2 || !ft_strstr(argv[1], ".s"))
		ft_error("file");
	assm.fd = open(argv[1], O_RDONLY);
	if (assm.fd <= -1)
		ft_error("file");
	ft_zero(&assm);
	ft_reader(&assm, line);
	close(assm.fd);
	ft_write(&assm, argv[1], 0);
	ft_free(&assm);
	return (0);
}

void	ft_zero(t_form *assm)
{
	assm->name = NULL;
	assm->comment = NULL;
	assm->is_n = 0;
	assm->is_c = 0;
	assm->is_cmd = 0;
	assm->is_com = 1;
	assm->hash = 0;
	assm->i = 0;
	assm->is_l = 0;
}

void	ft_reader(t_form *assm, char *line)
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
		else if ((assm->i_cmd = ft_find_command(assm, line)) != 17 || \
		assm->is_l == 1)
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
