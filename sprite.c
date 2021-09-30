/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:24:15 by nlaurids          #+#    #+#             */
/*   Updated: 2020/10/16 17:35:34 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub3d_spritesort(t_vars *vars, int spor[vars->config.spn],
		double spdist[vars->config.spn])
{
	int		f;
	int		temp;

	f = -1;
	while (++f < vars->config.spn - 1)
	{
		if (spdist[spor[f]] < spdist[spor[f + 1]])
		{
			temp = spor[f];
			spor[f] = spor[f + 1];
			spor[f + 1] = temp;
			f = -1;
		}
	}
}

static void	cub3d_spriterc1(t_vars *vars, int spor[vars->config.spn],
		double zbuf[vars->config.xres], int q)
{
	int r;

	r = 0;
	if (vars->spriterc.transformy > 0 && vars->spriterc.stripe >= 0
			&& vars->spriterc.stripe < vars->config.xres &&
			vars->spriterc.transformy < zbuf[vars->spriterc.stripe])
	{
		r = vars->spriterc.dstay;
		while (r < vars->spriterc.dendy)
		{
			vars->spriterc.stexy = (((r * 256 - vars->config.yres * 128
					+ vars->spriterc.sprh * 128) * vars->imgd.steh) /
					vars->spriterc.sprh) / 256;
			if (vars->spriterc.stexy < 0)
				vars->spriterc.stexy = 0;
			if ((tex_color_get(&vars->config.sprs[spor[q]].spt,
					vars->spriterc.stexx, vars->spriterc.stexy)
					& 0x00FFFFFF) != 0)
				my_mlx_pixel_put(&vars->img, vars->spriterc.stripe, r,
						tex_color_get(&vars->config.sprs[spor[q]].spt,
						vars->spriterc.stexx, vars->spriterc.stexy));
			r++;
		}
	}
}

static void	cub3d_spriterc0(t_vars *vars, int spor[vars->config.spn], int q)
{
	vars->spriterc.spritex = vars->config.sprs[spor[q]].spx -
			vars->sdir.posx;
	vars->spriterc.spritey = vars->config.sprs[spor[q]].spy -
			vars->sdir.posy;
	vars->spriterc.invdet = 1.0 / (vars->sdir.plnx * vars->sdir.diry -
			vars->sdir.dirx * vars->sdir.plny);
	vars->spriterc.transformx = vars->spriterc.invdet * (vars->sdir.diry *
			vars->spriterc.spritex - vars->sdir.dirx *
			vars->spriterc.spritey);
	vars->spriterc.transformy = vars->spriterc.invdet * (-vars->sdir.plny *
			vars->spriterc.spritex + vars->sdir.plnx *
			vars->spriterc.spritey);
	vars->spriterc.sprscrx = (int)((vars->config.xres / 2) *
			(1 + vars->spriterc.transformx /
			vars->spriterc.transformy));
	vars->spriterc.sprh = abs((int)(vars->config.yres /
			vars->spriterc.transformy));
	vars->spriterc.dstay = -vars->spriterc.sprh / 2 +
			vars->config.yres / 2;
	if (vars->spriterc.dstay < 0)
		vars->spriterc.dstay = 0;
	vars->spriterc.dendy = vars->spriterc.sprh / 2 + vars->config.yres / 2;
	if (vars->spriterc.dendy >= vars->config.yres)
		vars->spriterc.dendy = vars->config.yres;
}

static void	cub3d_spriterc2(t_vars *vars, int spor[vars->config.spn],
		double zbuf[vars->config.xres], int q)
{
	cub3d_spriterc0(vars, spor, q);
	vars->spriterc.sprw = abs((int)(vars->config.yres /
			vars->spriterc.transformy));
	vars->spriterc.dstax = -vars->spriterc.sprw / 2 +
			vars->spriterc.sprscrx;
	if (vars->spriterc.dstax < 0)
		vars->spriterc.dstax = 0;
	vars->spriterc.dendx = vars->spriterc.sprw / 2 +
			vars->spriterc.sprscrx;
	if (vars->spriterc.dendx >= vars->config.xres)
		vars->spriterc.dendx = vars->config.xres;
	vars->spriterc.stripe = vars->spriterc.dstax;
	while (vars->spriterc.stripe < vars->spriterc.dendx)
	{
		vars->spriterc.stexx = (int)(256 * (vars->spriterc.stripe -
				(-vars->spriterc.sprw / 2 + vars->spriterc.sprscrx)) *
				vars->imgd.stew / vars->spriterc.sprw) / 256;
		if (vars->spriterc.stexx < 0)
			vars->spriterc.stexx = 0;
		cub3d_spriterc1(vars, spor, zbuf, q);
		vars->spriterc.stripe++;
	}
}

void		cub3d_spriterc(t_vars *vars, double zbuf[vars->config.xres])
{
	int		spor[vars->config.spn];
	double	spdist[vars->config.spn];
	int		q;
	int		r;

	q = 0;
	r = 0;
	while (q < vars->config.spn)
	{
		spor[q] = q;
		spdist[q] = ((vars->sdir.posx - vars->config.sprs[q].spx) *
				(vars->sdir.posx - vars->config.sprs[q].spx) + (vars->sdir.posy
				- vars->config.sprs[q].spy) * (vars->sdir.posy -
				vars->config.sprs[q].spy));
		q++;
	}
	cub3d_spritesort(vars, spor, spdist);
	q = -1;
	while (++q < vars->config.spn)
		cub3d_spriterc2(vars, spor, zbuf, q);
}
