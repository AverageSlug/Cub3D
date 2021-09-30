/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 13:17:40 by nlaurids          #+#    #+#             */
/*   Updated: 2020/10/19 14:47:26 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exitcub3d(t_vars *vars)
{
	freeall(&vars->config);
	exit(0);
}

int	cub3d_key(t_vars *vars)
{
	vars->rot = 0.05;
	vars->mov = 0.05;
	vars->plux = 0.2;
	vars->pluy = 0.2;
	if (vars->sdir.dirx < 0)
		vars->plux = -vars->plux;
	if (vars->sdir.diry < 0)
		vars->pluy = -vars->pluy;
	mv_hor(vars);
	mv_ver(vars);
	look(vars);
	if (vars->hold == 1)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exitcub3d(vars);
	}
	return (0);
}

int	cub3d_key_press(int keycode, t_vars *vars)
{
	if (keycode == 0)
		vars->key.mv_hor = -1;
	if (keycode == 1)
		vars->key.mv_ver = 1;
	if (keycode == 2)
		vars->key.mv_hor = 1;
	if (keycode == 13)
		vars->key.mv_ver = -1;
	if (keycode == 123)
		vars->key.look = -1;
	if (keycode == 124)
		vars->key.look = 1;
	if (keycode == 53)
		vars->hold = 1;
	return (0);
}

int	cub3d_key_release(int keycode, t_vars *vars)
{
	if (keycode == 0)
		vars->key.mv_hor = 0;
	if (keycode == 1)
		vars->key.mv_ver = 0;
	if (keycode == 2)
		vars->key.mv_hor = 0;
	if (keycode == 13)
		vars->key.mv_ver = 0;
	if (keycode == 123)
		vars->key.look = 0;
	if (keycode == 124)
		vars->key.look = 0;
	return (0);
}
