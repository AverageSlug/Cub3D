/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:55:27 by nlaurids          #+#    #+#             */
/*   Updated: 2020/10/19 16:55:38 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub3d_parse_map1_bis(t_conf *config, int i, int j, int tspn)
{
	while (config->map[i][j])
	{
		if (config->map[i][j] == 'N' || config->map[i][j] == 'S' ||
				config->map[i][j] == 'W' || config->map[i][j] == 'E')
		{
			if (config->msp)
			{
				write(2, "Error\nMore than 1 starting position\n", 36);
				freeall(config);
				exit(-1);
			}
			config->msp = config->map[i][j];
			config->mspx = i + 0.5;
			config->mspy = j + 0.5;
		}
		if (config->map[i][j] == '2')
		{
			config->sprs[tspn].spx = i + 0.5;
			config->sprs[tspn].spy = j + 0.5;
			tspn++;
		}
		j++;
	}
}

static void	cub3d_parse_map1(t_conf *config)
{
	int i;
	int j;
	int tspn;

	i = 0;
	j = 0;
	tspn = 0;
	config->msp = '\0';
	while (config->map[i])
	{
		cub3d_parse_map1_bis(config, i, j, tspn);
		j = 0;
		i++;
	}
	if (!config->msp)
	{
		write(2, "Error\nNo starting position\n", 27);
		freeall(config);
		exit(-1);
	}
}

static void	cub3d_parse_map0(t_conf *config)
{
	int	b;

	config->spn = 0;
	b = cub3d_parse_map_a(config, 1, 0);
	if (b == 0)
	{
		write(2, "Error\nInvalid map\n", 18);
		freeall(config);
		exit(-1);
	}
	if (!(config->sprs = malloc(sizeof(t_sprite) * config->spn)))
	{
		write(2, "Error\nMalloc failed\n", 20);
		freeall(config);
		exit(-1);
	}
	cub3d_parse_map1(config);
}

static void	cub3d_parse_map_bis(t_conf *config, int ret, int fd, char *line)
{
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		if (line && line[0])
		{
			if (!cub3d_realloc(config->map, line, config->l, config))
			{
				write(2, "Error\nMalloc failed\n", 20);
				free(line);
				freeall(config);
				exit(-1);
			}
			config->l++;
			if (config->temp[8] == 0)
				config->temp[8] = 1;
			if (config->temp[8] == 2)
				config->temp[8] = 3;
		}
		else if (config->temp[8] == 1)
			config->temp[8] = 2;
		free(line);
		if (ret == 0)
			break ;
	}
}

void		cub3d_parse_map(t_conf *config, int fd)
{
	int		ret;
	char	*line;

	config->map = NULL;
	config->temp[8] = 0;
	config->l = 0;
	ret = 0;
	line = NULL;
	cub3d_parse_map_bis(config, ret, fd, line);
	if (ret == -1 || config->temp[8] == 3 || config->l <= 2)
	{
		if (ret == -1)
			write(2, "Error\nGetting line failed - Check your file\n", 44);
		else if (config->temp[8] == 3 || config->l <= 2)
			write(2, "Error\nInvalid map\n", 18);
		freeall(config);
		exit(-1);
	}
	cub3d_parse_map0(config);
}
