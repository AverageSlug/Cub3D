/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:45:34 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 17:58:09 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		is_digit(char *c)
{
	int i;

	i = 0;
	while (c[i])
	{
		if (!(c[i] >= '0' && c[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int		freeturn(char **data, int ret)
{
	if (data)
	{
		free(*data);
		*data = NULL;
	}
	return (ret);
}

void	freeall(t_conf *config)
{
	int i;

	i = 0;
	if (config->map)
	{
		while (config->map[i])
		{
			free(config->map[i]);
			config->map[i++] = NULL;
		}
		free(config->map);
		config->map = NULL;
	}
	if (config->no)
		free(config->no);
	if (config->so)
		free(config->so);
	if (config->we)
		free(config->we);
	if (config->ea)
		free(config->ea);
	if (config->s)
		free(config->s);
	if (config->sprs)
		free(config->sprs);
}
