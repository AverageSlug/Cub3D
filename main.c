/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:05:05 by nlaurids          #+#    #+#             */
/*   Updated: 2020/11/06 12:19:04 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	checkfile(int fd, char **argv)
{
	int i;

	i = 0;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (-1);
	while (argv[1][i])
		i++;
	if (i < 5)
		return (-1);
	if (argv[1][--i] != 'b')
		return (-1);
	if (argv[1][--i] != 'u')
		return (-1);
	if (argv[1][--i] != 'c')
		return (-1);
	if (argv[1][--i] != '.')
		return (-1);
	return (fd);
}

static int	checkargs(int fd, int argc, char **argv, t_vars *vars)
{
	if (argc != 3)
	{
		if (argc != 2)
		{
			write(2, "Error\nIncorrect amount of arguments\n", 36);
			return (-1);
		}
	}
	else if (argv[2][0] == '-' && argv[2][1] == '-'
				&& argv[2][2] == 's' && argv[2][3] == 'a'
				&& argv[2][4] == 'v' && argv[2][5] == 'e' && !argv[2][6])
		vars->save = 1;
	else
	{
		write(2, "Error\nIncorrect 3rd argument, must be --save\n", 45);
		return (-1);
	}
	if ((fd = checkfile(fd, argv)) < 0)
	{
		if (fd == -1)
			write(2, "Error\nIncorrect filename - Check the name\n", 42);
		return (-1);
	}
	return (fd);
}

static void	setconf(t_conf *config)
{
	config->temp[0] = 0;
	config->temp[1] = 0;
	config->temp[2] = 0;
	config->temp[3] = 0;
	config->temp[4] = 0;
	config->temp[5] = 0;
	config->temp[6] = 0;
	config->temp[7] = 0;
	config->temp[8] = 0;
}

void		main2(t_vars *vars)
{
	if (vars->save == 0)
		cub3d_mlx(vars);
	else
	{
		vars->mlx = mlx_init();
		cub3d_set(vars);
		cub3d_fc(*vars, vars->a);
		cub3d_raycast(vars);
		save_bitmap("screenshot.bmp", vars);
	}
}

int			main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		ret;
	t_vars	vars;

	fd = 1;
	vars.save = 0;
	setconf(&vars.config);
	if ((fd = checkargs(fd, argc, argv, &vars)) == -1)
		exit(-1);
	while (vars.config.temp[8] < 8 && (ret = get_next_line(fd, &line)) == 1)
	{
		vars.config.realine = cub3d_split(line, ' ');
		free(line);
		cub3d_parse(&vars.config);
	}
	if (ret == -1)
	{
		write(2, "Error\nGetting line failed - Check your file\n", 44);
		freeall(&vars.config);
		exit(-1);
	}
	cub3d_parse_map(&vars.config, fd);
	main2(&vars);
}
