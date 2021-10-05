/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:29:53 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 17:57:59 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		cub3d_verline(t_vars *vars, int i)
{
	int	d;

	vars->tex.tstp = 1.0 * vars->tex.texh / vars->sdir.lh;
	vars->tex.tpos = (vars->sdir.dsta - vars->config.yres / 2 +
			vars->sdir.lh / 2) * vars->tex.tstp;
	d = vars->sdir.dsta;
	while (d < vars->sdir.dend)
	{
		vars->tex.texy = (int)vars->tex.tpos & (vars->tex.texh - 1);
		vars->tex.tpos += vars->tex.tstp;
		my_mlx_pixel_put(&vars->img, i, d, tex_color_get(&vars->tex.texd,
				vars->tex.texx, vars->tex.texy));
		d++;
	}
}

static void	cub3d_raycasting0(t_vars *vars)
{
	vars->sdir.lh = (int)(vars->config.yres / vars->sdir.pwd);
	vars->sdir.dsta = -vars->sdir.lh / 2 + vars->config.yres / 2;
	if (vars->sdir.dsta < 0)
		vars->sdir.dsta = 0;
	vars->sdir.dend = vars->sdir.lh / 2 + vars->config.yres / 2;
	if (vars->sdir.dend > vars->config.yres)
		vars->sdir.dend = vars->config.yres;
	if (vars->sdir.side == 0)
		vars->tex.walx = vars->sdir.posy + vars->sdir.pwd * vars->sdir.rayy;
	else
		vars->tex.walx = vars->sdir.posx + vars->sdir.pwd * vars->sdir.rayx;
	vars->tex.walx -= floor(vars->tex.walx);
	cub3d_texside(vars);
	vars->tex.texx = (int)(vars->tex.walx * (double)vars->tex.texw);
	if (vars->sdir.side == 0 && vars->sdir.rayx > 0)
		vars->tex.texx = vars->tex.texw - vars->tex.texx - 1;
	if (vars->sdir.side == 1 && vars->sdir.rayy < 0)
		vars->tex.texx = vars->tex.texw - vars->tex.texx - 1;
}

void		cub3d_raycasting(t_vars *vars)
{
	while (vars->sdir.hit == 0)
	{
		if (vars->sdir.sidx < vars->sdir.sidy)
		{
			vars->sdir.sidx += vars->sdir.delx;
			vars->sdir.mpx += vars->sdir.stpx;
			vars->sdir.side = 0;
		}
		else
		{
			vars->sdir.sidy += vars->sdir.dely;
			vars->sdir.mpy += vars->sdir.stpy;
			vars->sdir.side = 1;
		}
		if (vars->config.map[vars->sdir.mpx][vars->sdir.mpy] == '1')
			vars->sdir.hit = 1;
	}
	if (vars->sdir.side == 0)
		vars->sdir.pwd = (vars->sdir.mpx - vars->sdir.posx +
				(1 - vars->sdir.stpx) / 2) / vars->sdir.rayx;
	else
		vars->sdir.pwd = (vars->sdir.mpy - vars->sdir.posy +
				(1 - vars->sdir.stpy) / 2) / vars->sdir.rayy;
	cub3d_raycasting0(vars);
}

void		cub3d_setdir2(t_vars *vars)
{
	if (vars->sdir.rayx < 0)
	{
		vars->sdir.stpx = -1;
		vars->sdir.sidx = (vars->sdir.posx - vars->sdir.mpx) * vars->sdir.delx;
	}
	else
	{
		vars->sdir.stpx = 1;
		vars->sdir.sidx = (vars->sdir.mpx + 1.0 - vars->sdir.posx) *
			vars->sdir.delx;
	}
	if (vars->sdir.rayy < 0)
	{
		vars->sdir.stpy = -1;
		vars->sdir.sidy = (vars->sdir.posy - vars->sdir.mpy) * vars->sdir.dely;
	}
	else
	{
		vars->sdir.stpy = 1;
		vars->sdir.sidy = (vars->sdir.mpy + 1.0 - vars->sdir.posy) *
			vars->sdir.dely;
	}
}
