/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:34:14 by nlaurids          #+#    #+#             */
/*   Updated: 2020/10/19 13:33:20 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fillbits(unsigned char *bitmap, unsigned int value)
{
	unsigned int *ptr;

	ptr = (unsigned int*)bitmap;
	*ptr = value;
}

static void	save_bitmap_color(const char *file_name, t_vars *vars,
		unsigned char bitmap[54], int i)
{
	int	j;
	int fd;
	int color;

	j = 0;
	if ((fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
	{
		write(2, "Error\nOpen failed\n", 17);
		freeall(&vars->config);
		exit(-1);
	}
	write(fd, bitmap, 54);
	while (++i < vars->config.yres)
	{
		while (j < vars->config.xres)
		{
			color = tex_color_get(&vars->img, j, i);
			write(fd, &color, 3);
			j++;
		}
		color = 0;
		write(fd, &color, ((4 - ((vars->config.xres * 3) % 4)) % 4));
		j = 0;
	}
	close(fd);
}

void		save_bitmap(const char *file_name, t_vars *vars)
{
	int				i;
	unsigned char	bitmap[54];

	i = 0;
	while (i < 54)
		bitmap[i++] = 0;
	bitmap[0] = 'B';
	bitmap[1] = 'M';
	fillbits(bitmap + 2, 54 + 3 * vars->config.xres * vars->config.yres
			+ vars->config.yres * ((4 - ((vars->config.xres * 3) % 4)) % 4));
	bitmap[10] = 54;
	bitmap[14] = 40;
	fillbits(bitmap + 18, vars->config.xres);
	fillbits(bitmap + 22, -vars->config.yres);
	bitmap[26] = 1;
	bitmap[28] = 24;
	fillbits(bitmap + 34, 3 * vars->config.xres * vars->config.yres);
	i = -1;
	save_bitmap_color(file_name, vars, bitmap, i);
}
