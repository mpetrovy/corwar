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


unsigned int ft_get_prog_size(unsigned char *buf, int i)
{
	return ((buf[i] << 24) | (buf[i + 1] << 16) | (buf[i + 2] << 8) | (buf[i + 3]));
}

void	ft_write_code(t_plr *p, unsigned char *buf, int i)
{
	unsigned int j;

	if (!(p->code = (unsigned char*)malloc(sizeof(unsigned char) * (p->head.prog_size+1))))
		return ;

	j = 0;
	while (j < p->head.prog_size)
	{
		p->code[j++] =  buf[i++];
	}
	printf("%x\n", buf[i]);
	if (buf[i] != '\0')
		printf("ERROR\n");
}

void		ft_fill(t_plr *p, unsigned char *buf)
{
	int i;
	int j;

	//printf("here\n");
	i = 4;
	if (buf[0] == 0 && buf[1] == 234 && buf[2] == 131 && buf[3] == 243)
		p->head.magic = 15369203;
	j = 0;
	while (i < 132)
	{
		printf("value = |%x|\n", buf[i]);
		p->head.prog_name[j++] = buf[i++];
	}
	//printf("datat %x %x %x %x\n", buf[i], buf[i + 1], buf[i+2], buf[i+3]);
	if (buf[i] != 0 || buf[i + 1] != 0 || buf[i + 2] != 0 || buf[i + 3] != 0)
	{
		printf("Error Null not exist\n");
		exit (-1);
	}
	i += 4;
	//printf("datat %x %x %x %x\n", buf[i], buf[i + 1], buf[i+2], buf[i+3]);
	p->head.prog_size = ft_get_prog_size(buf, i);
	i += 4;
	j = 0;
	while (i < 2188)
		p->head.comment[j++] = buf[i++];
	if (buf[i] != 0 || buf[i + 1] != 0 || buf[i+2] != 0 || buf[i+3] != 0)
	{
		printf("Error second null not exist\n");
		exit(-1);
	}
	i += 4;
	ft_write_code(p, buf, i);
//	printf("last %x\n", buf[2214]);
//	printf("magic %x\n", p->head.magic);
//	printf("come %s\n", p->head.comment);
}

void	ft_read(t_plr *p)
{
	int				fd;
	int				res;
	unsigned char	buf[READ_SIZE];

	fd = -1;
	//printf("name of file %s\n", p->file_name);
	if ((fd = open(p->file_name, O_RDONLY)) == -1)
		printf("Error read file\n");
	while ((res = read(fd, buf, READ_SIZE)) > 0)
		buf[res] = '\0';	
	if (close(fd) == -1)
		printf("close error\n");
	ft_fill(p, buf);
}

void	ft_read_cor(t_env *e, int ac)
{
	int i;

	(void)ac;
	i = 0;
	//printf("ac %d\n", ac);
	while (i < e->plr_numb)
	{
		ft_read(&e->plrs[i]);
		i++;
	}

	//printf("Its end\n");
}
