/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:22:04 by nlaurids          #+#    #+#             */
/*   Updated: 2020/10/06 14:48:08 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	badtex(t_conf *config, int d)
{
	freerealine(config->realine);
	if (d == 0)
		write(2, "Error\nDouble NO\n", 16);
	if (d == 1)
		write(2, "Error\nInvalid amount of arguments for NO\n", 41);
	if (d == 2)
		write(2, "Error\nDouble SO\n", 16);
	if (d == 3)
		write(2, "Error\nInvalid amount of arguments for SO\n", 41);
	if (d == 4)
		write(2, "Error\nDouble WE\n", 16);
	if (d == 5)
		write(2, "Error\nInvalid amount of arguments for WE\n", 41);
	if (d == 6)
		write(2, "Error\nDouble EA\n", 16);
	if (d == 7)
		write(2, "Error\nInvalid amount of arguments for EA\n", 41);
	freeall(config);
	exit(-1);
}

void		cub3d_parse_ea(t_conf *config)
{
	if (config->realine[0][0] == 'E' && config->realine[0][1] == 'A' &&
			!config->realine[0][2])
	{
		if (config->temp[4] == 1)
			badtex(config, 6);
		if (!config->realine[1] || config->realine[2])
			badtex(config, 7);
		config->ea = cub3d_strdup(config->realine[1]);
		freerealine(config->realine);
		config->temp[4] = 1;
		config->temp[8]++;
		return ;
	}
	cub3d_parse_s(config);
}

void		cub3d_parse_we(t_conf *config)
{
	if (config->realine[0][0] == 'W' && config->realine[0][1] == 'E' &&
			!config->realine[0][2])
	{
		if (config->temp[3] == 1)
			badtex(config, 4);
		if (!config->realine[1] || config->realine[2])
			badtex(config, 5);
		config->we = cub3d_strdup(config->realine[1]);
		freerealine(config->realine);
		config->temp[3] = 1;
		config->temp[8]++;
		return ;
	}
	cub3d_parse_ea(config);
}

void		cub3d_parse_so(t_conf *config)
{
	if (config->realine[0][0] == 'S' && config->realine[0][1] == 'O' &&
			!config->realine[0][2])
	{
		if (config->temp[2] == 1)
			badtex(config, 2);
		if (!config->realine[1] || config->realine[2])
			badtex(config, 3);
		config->so = cub3d_strdup(config->realine[1]);
		freerealine(config->realine);
		config->temp[2] = 1;
		config->temp[8]++;
		return ;
	}
	cub3d_parse_we(config);
}

void		cub3d_parse_no(t_conf *config)
{
	if (config->realine[0][0] == 'N' && config->realine[0][1] == 'O' &&
			!config->realine[0][2])
	{
		if (config->temp[1] == 1)
			badtex(config, 0);
		if (!config->realine[1] || config->realine[2])
			badtex(config, 1);
		config->no = cub3d_strdup(config->realine[1]);
		freerealine(config->realine);
		config->temp[1] = 1;
		config->temp[8]++;
		return ;
	}
	cub3d_parse_so(config);
}
