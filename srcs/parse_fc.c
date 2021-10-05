/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:50:38 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 17:57:42 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	badfc(t_conf *config, int d)
{
	freerealine(config->realine);
	if (d == 2)
		write(2, "Error\nDouble F\n", 15);
	if (d == 3)
		write(2, "Error\nInvalid amount of arguments for F\n", 40);
	if (d == 4)
		write(2, "Error\nDouble C\n", 15);
	if (d == 5)
		write(2, "Error\nInvalid amount of arguments for C\n", 40);
	if (d == 6)
		write(2, "Error\nInvalid F color\n", 22);
	if (d == 7)
		write(2, "Error\nInvalid C color\n", 22);
	freeall(config);
	exit(-1);
}

static char	**cub3d_parse_c0(t_conf *config, char **templ, int u, int v)
{
	while (config->realine[1][v])
	{
		if (config->realine[1][v] == ',')
			u++;
		v++;
	}
	if (u > 2)
		badfc(config, 7);
	if (!config->realine[1] || config->realine[2])
		badfc(config, 5);
	templ = cub3d_split(config->realine[1], ',');
	if (!templ[0] || !templ[1] || !templ[2] || templ[3])
	{
		freerealine(templ);
		badfc(config, 5);
	}
	if (!(cub3d_atoi(templ[0]) >= 0 && cub3d_atoi(templ[0]) <= 255 &&
			cub3d_atoi(templ[1]) >= 0 && cub3d_atoi(templ[1]) <= 255 &&
			cub3d_atoi(templ[2]) >= 0 && cub3d_atoi(templ[2]) <= 255 &&
			is_digit(templ[0]) && is_digit(templ[1]) && is_digit(templ[2])))
	{
		freerealine(templ);
		badfc(config, 7);
	}
	return (templ);
}

void		cub3d_parse_c(t_conf *config)
{
	char	**templ;
	int		u;
	int		v;

	templ = NULL;
	if (config->realine[0][0] == 'C' && !config->realine[0][1])
	{
		if (config->temp[7] == 1)
			badfc(config, 4);
		u = 0;
		v = 0;
		templ = cub3d_parse_c0(config, templ, u, v);
		config->c[0] = cub3d_atoi(templ[0]);
		config->c[1] = cub3d_atoi(templ[1]);
		config->c[2] = cub3d_atoi(templ[2]);
		freerealine(config->realine);
		freerealine(templ);
		config->temp[7] = 1;
		config->temp[8]++;
		return ;
	}
	freerealine(config->realine);
	write(1, "Error\nInvalid file content\n", 27);
	exit(0);
}

static char	**cub3d_parse_f0(t_conf *config, char **templ, int u, int v)
{
	while (config->realine[1][v])
	{
		if (config->realine[1][v] == ',')
			u++;
		v++;
	}
	if (u > 2)
		badfc(config, 6);
	if (!config->realine[1] || config->realine[2])
		badfc(config, 3);
	templ = cub3d_split(config->realine[1], ',');
	if (!templ[0] || !templ[1] || !templ[2] || templ[3])
	{
		freerealine(templ);
		badfc(config, 3);
	}
	if (!(cub3d_atoi(templ[0]) >= 0 && cub3d_atoi(templ[0]) <= 255 &&
			cub3d_atoi(templ[1]) >= 0 && cub3d_atoi(templ[1]) <= 255 &&
			cub3d_atoi(templ[2]) >= 0 && cub3d_atoi(templ[2]) <= 255 &&
			is_digit(templ[0]) && is_digit(templ[1]) && is_digit(templ[2])))
	{
		freerealine(templ);
		badfc(config, 6);
	}
	return (templ);
}

void		cub3d_parse_f(t_conf *config)
{
	char	**templ;
	int		u;
	int		v;

	templ = NULL;
	if (config->realine[0][0] == 'F' && !config->realine[0][1])
	{
		if (config->temp[6] == 1)
			badfc(config, 2);
		u = 0;
		v = 0;
		templ = cub3d_parse_f0(config, templ, u, v);
		config->f[0] = cub3d_atoi(templ[0]);
		config->f[1] = cub3d_atoi(templ[1]);
		config->f[2] = cub3d_atoi(templ[2]);
		freerealine(config->realine);
		freerealine(templ);
		config->temp[6] = 1;
		config->temp[8]++;
		return ;
	}
	cub3d_parse_c(config);
}
