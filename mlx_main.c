/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:28:33 by nlaurids          #+#    #+#             */
/*   Updated: 2020/11/06 12:26:28 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			cub3d_raycast_loop(t_vars *vars)
{
	cub3d_key(vars);
	cub3d_fc(*vars, vars->a);
	cub3d_raycast(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (1);
}

void		cub3d_fc(t_vars vars, int a[2])
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < vars.config.yres / 2)
	{
		while (j < vars.config.xres)
		{
			my_mlx_pixel_put(&vars.img, j, i, a[1]);
			j++;
		}
		j = 0;
		i++;
	}
	while (i < vars.config.yres)
	{
		while (j < vars.config.xres)
		{
			my_mlx_pixel_put(&vars.img, j, i, a[0]);
			j++;
		}
		j = 0;
		i++;
	}
}

void		cub3d_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx,
			vars->config.xres, vars->config.yres, "cub3D");
	cub3d_set(vars);
	vars->key.mv_hor = 0;
	vars->key.mv_ver = 0;
	vars->key.look = 0;
	mlx_hook(vars->win, 2, 1L << 0, cub3d_key_press, vars);
	mlx_hook(vars->win, 3, 1L << 1, cub3d_key_release, vars);
	mlx_loop_hook(vars->mlx, cub3d_raycast_loop, vars);
	mlx_hook(vars->win, 17, 0, exitcub3d, vars);
	mlx_loop(vars->mlx);
}
