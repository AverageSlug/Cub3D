/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:53:06 by nlaurids          #+#    #+#             */
/*   Updated: 2020/10/19 16:52:20 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cub3d_parse_map_fl(t_conf *config)
{
	int j;

	j = 0;
	config->mxs[0] = ft_strlen(config->map[1]);
	while (config->map[0][j])
	{
		cub3d_set_ac(config->ac, config->map[0][j], j, config->mxs[0]);
		if (config->map[0][j] != ' ' && config->map[0][j] != '1')
			return (0);
		if (config->map[0][j] == ' ')
			if (j < config->mxs[0] &&
					!config->ac[(unsigned char)config->map[1][j]])
				return (0);
		j++;
	}
	return (1);
}

static int	cub3d_parse_map_ll(t_conf *config, int i)
{
	int j;

	j = 0;
	config->mxs[1] = ft_strlen(config->map[i - 1]);
	while (config->map[i][j])
	{
		cub3d_set_ac(config->ac, config->map[i][j], j, config->mxs[1]);
		if (config->map[i][j] != ' ' && config->map[i][j] != '1')
			return (0);
		if (config->map[i][j] == ' ')
			if (j < config->mxs[1] &&
					!config->ac[(unsigned char)config->map[i - 1][j]])
				return (0);
		j++;
	}
	return (1);
}

static int	cub3d_parse_map_a_bis(t_conf *config, int i, int j)
{
	if (config->map[i][j] != '1' && (config->map[i][j] != ' ' ||
			(config->map[i][j] == ' ' &&
			(j < config->mxs[1] && j < config->mxs[2]))))
	{
		if (config->ac[(unsigned char)config->map[i][j]])
		{
			cub3d_set_ac(config->ac, config->map[i][j], j, config->mxs[0]);
			if ((j <= config->mxs[1] &&
					!config->ac[(unsigned char)config->map[i - 1]
					[j]]) || (j <= config->mxs[2] &&
					!config->ac[(unsigned char)config->map[i + 1][j]]))
				return (0);
			if (config->map[i][j] == '2')
				config->spn++;
		}
		else
			return (0);
	}
	else if (config->ac[(unsigned char)config->map[i][j]])
		cub3d_set_ac(config->ac, config->map[i][j], j, config->mxs[0]);
	else
		return (0);
	return (1);
}

int			cub3d_parse_map_a(t_conf *config, int i, int j)
{
	if (!cub3d_parse_map_fl(config))
		return (0);
	cub3d_set_mxs(config->mxs, config->map, i);
	cub3d_set_ac(config->ac, 0, j, config->mxs[0]);
	while (i < config->l - 1)
	{
		j = 0;
		cub3d_set_mxs(config->mxs, config->map, i);
		while (config->map[i][j])
		{
			if (!cub3d_parse_map_a_bis(config, i, j))
				return (0);
			j++;
		}
		if (config->map[i][j - 1] != '1' && config->map[i][j - 1]
				!= ' ' && j <= config->mxs[0])
			return (0);
		i++;
		cub3d_set_ac(config->ac, 0, j, config->mxs[0]);
	}
	if (!cub3d_parse_map_ll(config, i))
		return (0);
	return (1);
}
