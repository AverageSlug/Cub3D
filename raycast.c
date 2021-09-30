/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:40:35 by nlaurids          #+#    #+#             */
/*   Updated: 2020/10/02 12:22:20 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub3d_setdir1(t_vars *vars)
{
	int		i;
	double	zbuf[vars->config.xres];

	i = 0;
	while (i < vars->config.xres)
	{
		vars->sdir.camx = 2 * i / (double)vars->config.xres - 1;
		vars->sdir.rayx = vars->sdir.dirx + vars->sdir.plnx * vars->sdir.camx;
		vars->sdir.rayy = vars->sdir.diry + vars->sdir.plny * vars->sdir.camx;
		vars->sdir.mpx = (int)(vars->sdir.posx);
		vars->sdir.mpy = (int)(vars->sdir.posy);
		vars->sdir.delx = fabs(1 / vars->sdir.rayx);
		vars->sdir.dely = fabs(1 / vars->sdir.rayy);
		vars->sdir.hit = 0;
		cub3d_setdir2(vars);
		cub3d_raycasting(vars);
		zbuf[i] = vars->sdir.pwd;
		cub3d_verline(vars, i);
		i++;
	}
	if (vars->config.spn >= 1)
		cub3d_spriterc(vars, zbuf);
}

static void	cub3d_setdir0(t_vars *vars)
{
	if (vars->config.msp == 'W')
	{
		vars->sdir.dirx = 0;
		vars->sdir.diry = -1;
		vars->sdir.plnx = -0.66;
		vars->sdir.plny = 0;
	}
	if (vars->config.msp == 'E')
	{
		vars->sdir.dirx = 0;
		vars->sdir.diry = 1;
		vars->sdir.plnx = 0.66;
		vars->sdir.plny = 0;
	}
	vars->sdir.posx = vars->config.mspx;
	vars->sdir.posy = vars->config.mspy;
}

void		cub3d_setdir(t_vars *vars)
{
	if (vars->config.msp == 'N')
	{
		vars->sdir.dirx = -1;
		vars->sdir.diry = 0;
		vars->sdir.plnx = 0;
		vars->sdir.plny = 0.66;
	}
	if (vars->config.msp == 'S')
	{
		vars->sdir.dirx = 1;
		vars->sdir.diry = 0;
		vars->sdir.plnx = 0;
		vars->sdir.plny = -0.66;
	}
	cub3d_setdir0(vars);
}

void		cub3d_raycast(t_vars *vars)
{
	cub3d_setdir1(vars);
}
