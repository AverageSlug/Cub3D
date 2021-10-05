/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sres.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 15:47:38 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 17:57:50 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	badsres(t_conf *config, int d)
{
	freerealine(config->realine);
	if (d == 0)
		write(2, "Error\nInvalid amount of arguments for resolution\n", 49);
	if (d == 1)
		write(2, "Error\nDouble resolution\n", 24);
	if (d == 2)
		write(2, "Error\nInvalid resolution\n", 25);
	if (d == 3)
		write(2, "Error\nDouble S\n", 15);
	if (d == 4)
		write(2, "Error\nInvalid amount of arguments for S\n", 40);
	freeall(config);
	exit(-1);
}

void		cub3d_parse_s(t_conf *config)
{
	if (config->realine[0][0] == 'S' && !config->realine[0][1])
	{
		if (config->temp[5] == 1)
			badsres(config, 3);
		if (!config->realine[1] || config->realine[2])
			badsres(config, 4);
		config->s = cub3d_strdup(config->realine[1]);
		freerealine(config->realine);
		config->temp[5] = 1;
		config->temp[8]++;
		return ;
	}
	cub3d_parse_f(config);
}

void		cub3d_parse(t_conf *config)
{
	if (!config->realine[0])
		return ;
	if (config->realine[0][0] == 'R' && !config->realine[0][1])
	{
		if (!config->realine[1] || !config->realine[2] || config->realine[3])
			badsres(config, 0);
		if (config->temp[0] == 1)
			badsres(config, 1);
		if (!(is_digit(config->realine[1]) && is_digit(config->realine[2])))
			badsres(config, 2);
		config->xres = cub3d_atoi(config->realine[1]);
		config->yres = cub3d_atoi(config->realine[2]);
		if (config->xres > 2560)
			config->xres = 2560;
		if (config->yres > 1440)
			config->yres = 1440;
		if (config->xres <= 0 || config->yres <= 0)
			badsres(config, 2);
		freerealine(config->realine);
		config->temp[0] = 1;
		config->temp[8]++;
		return ;
	}
	cub3d_parse_no(config);
}
