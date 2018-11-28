/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdcor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:25:42 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/06 15:25:43 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static unsigned int ft_get_prog_size(unsigned char *buf, int i)
{
	return ((buf[i] << 24) | (buf[i + 1] << 16) | (buf[i + 2] << 8) | (buf[i + 3]));
}

static void			ft_write_code(t_plr *p, unsigned char *buf, int i)
{
	unsigned int j;

	j = 0;
	if (!(p->code = (unsigned char*)malloc(sizeof(unsigned char) * (p->head.prog_size))))
		return ;
	while (j < p->head.prog_size)
	{
		p->code[j++] = buf[i++];
	}
	if (i != p->file_size)
		ft_error(p->file_name, "file is more then shown");
}

static void			ft_fill(t_plr *p, unsigned char *buf)
{
	int i;
	int j;

	i = 4;
	if (buf[0] == 0 && buf[1] == 234 && buf[2] == 131 && buf[3] == 243)
		p->head.magic = 15369203;
	else
		ft_error(p->file_name, "magic line not exist");
	j = 0;
	while (i < 132)
		p->head.prog_name[j++] = buf[i++];
	if (buf[i] != 0 || buf[i + 1] != 0 || buf[i + 2] != 0 || buf[i + 3] != 0)
		ft_error(p->file_name, "Champion name too long (Max length 128)");
	i += 4;
	if ((p->head.prog_size = ft_get_prog_size(buf, i)) > CHAMP_MAX_SIZE)
		ft_error(p->file_name, "Error: File champs/42.cor copy has too large\
		 a code (993 bytes > 682 bytes)");
	i += 4;
	j = 0;
	while (i < 2188)
		p->head.comment[j++] = buf[i++];
	if (buf[i] != 0 || buf[i + 1] != 0 || buf[i+2] != 0 || buf[i+3] != 0)
		ft_error(p->file_name, "second null not exist");
	i += 4;
	ft_write_code(p, buf, i);
}

static void			ft_read(t_plr *p)
{
	int				fd;
	int				res;
	int				empty;
	unsigned char	buf[READ_SIZE];

	fd = -1;
	empty = 1;
	if ((fd = open(p->file_name, O_RDONLY)) == -1)
		ft_error(p->file_name, "file not exist");
	while ((res = read(fd, buf, READ_SIZE)) > 0)
	{
		empty = 0;
		if (res > 4096)
			ft_error(p->file_name, "file is too long");
		p->file_size = res;
		buf[res] = '\0';
	}
	if (close(fd) == -1)
		ft_error(p->file_name, "can not close");
	if (empty)
		ft_error(p->file_name, "file is empty");
	ft_fill(p, buf);
}

void				ft_read_cor(t_env *e, int ac)
{
	int i;

	(void)ac;
	i = 0;
	printf("Introducing contestants...\n");
	while (i < e->plr_numb)
	{
		ft_read(&e->plrs[i]);
		printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n", i + 1,
		e->plrs[i].head.prog_size, e->plrs[i].head.prog_name, e->plrs[i].head.comment);// change to ft_printf();
		i++;
	}
	if (e->plr_numb == 0)
		ft_error("", "not enoug files");
}
