/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:52:59 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 17:58:12 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	cub3d_texside0(t_vars *vars)
{
	if (vars->sdir.side != 0)
	{
		if (vars->sdir.rayy > 0)
		{
			vars->tex.tex = vars->imgd.eatex;
			vars->tex.texw = vars->imgd.eatew;
			vars->tex.texh = vars->imgd.eateh;
			vars->tex.texd = vars->imgd.eadat;
		}
		else
		{
			vars->tex.tex = vars->imgd.wetex;
			vars->tex.texw = vars->imgd.wetew;
			vars->tex.texh = vars->imgd.weteh;
			vars->tex.texd = vars->imgd.wedat;
		}
	}
}

void		cub3d_texside(t_vars *vars)
{
	if (vars->sdir.side == 0)
	{
		if (vars->sdir.rayx > 0)
		{
			vars->tex.tex = vars->imgd.sotex;
			vars->tex.texw = vars->imgd.sotew;
			vars->tex.texh = vars->imgd.soteh;
			vars->tex.texd = vars->imgd.sodat;
		}
		else
		{
			vars->tex.tex = vars->imgd.notex;
			vars->tex.texw = vars->imgd.notew;
			vars->tex.texh = vars->imgd.noteh;
			vars->tex.texd = vars->imgd.nodat;
		}
	}
	cub3d_texside0(vars);
}

static void	cub3d_imgpath(t_vars *vars)
{
	vars->imgd.notex = mlx_xpm_file_to_image(vars->mlx, vars->config.no,
			&vars->imgd.notew, &vars->imgd.noteh);
	vars->imgd.sotex = mlx_xpm_file_to_image(vars->mlx, vars->config.so,
			&vars->imgd.sotew, &vars->imgd.soteh);
	vars->imgd.wetex = mlx_xpm_file_to_image(vars->mlx, vars->config.we,
			&vars->imgd.wetew, &vars->imgd.weteh);
	vars->imgd.eatex = mlx_xpm_file_to_image(vars->mlx, vars->config.ea,
			&vars->imgd.eatew, &vars->imgd.eateh);
	vars->imgd.stex = mlx_xpm_file_to_image(vars->mlx, vars->config.s,
			&vars->imgd.stew, &vars->imgd.steh);
	if (!vars->imgd.notex || !vars->imgd.sotex ||
			!vars->imgd.wetex || !vars->imgd.eatex || !vars->imgd.stex)
	{
		write(2, "Error\nTexture open failed\n", 26);
		freeall(&vars->config);
		exit(-1);
	}
	if (vars->imgd.noteh != vars->imgd.notew || vars->imgd.soteh !=
			vars->imgd.sotew || vars->imgd.weteh != vars->imgd.wetew
			|| vars->imgd.eateh != vars->imgd.eatew)
	{
		write(2, "Error\nWrong Texture dimension\n", 30);
		freeall(&vars->config);
		exit(-1);
	}
}

static void	cub3d_set0(t_vars *vars)
{
	vars->imgd.nodat.addr = mlx_get_data_addr(vars->imgd.notex,
			&vars->imgd.nodat.bits_per_pixel, &vars->imgd.nodat.line_length,
			&vars->imgd.nodat.endian);
	vars->imgd.sodat.addr = mlx_get_data_addr(vars->imgd.sotex,
			&vars->imgd.sodat.bits_per_pixel, &vars->imgd.sodat.line_length,
			&vars->imgd.sodat.endian);
	vars->imgd.wedat.addr = mlx_get_data_addr(vars->imgd.wetex,
			&vars->imgd.wedat.bits_per_pixel, &vars->imgd.wedat.line_length,
			&vars->imgd.wedat.endian);
	vars->imgd.eadat.addr = mlx_get_data_addr(vars->imgd.eatex,
			&vars->imgd.eadat.bits_per_pixel, &vars->imgd.eadat.line_length,
			&vars->imgd.eadat.endian);
	vars->imgd.sdat.addr = mlx_get_data_addr(vars->imgd.stex,
			&vars->imgd.sdat.bits_per_pixel, &vars->imgd.sdat.line_length,
			&vars->imgd.sdat.endian);
}

void		cub3d_set(t_vars *vars)
{
	int spr;

	spr = 0;
	cub3d_setdir(vars);
	vars->a[0] = create_trgb(0,
			vars->config.f[0], vars->config.f[1], vars->config.f[2]);
	vars->a[1] = create_trgb(0,
			vars->config.c[0], vars->config.c[1], vars->config.c[2]);
	cub3d_imgpath(vars);
	vars->img.img = mlx_new_image(vars->mlx,
			vars->config.xres, vars->config.yres);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	cub3d_set0(vars);
	while (spr < vars->config.spn)
	{
		vars->config.sprs[spr].spt.img = vars->imgd.sdat.img;
		vars->config.sprs[spr].spt.addr = vars->imgd.sdat.addr;
		vars->config.sprs[spr].spt.bits_per_pixel =
				vars->imgd.sdat.bits_per_pixel;
		vars->config.sprs[spr].spt.line_length = vars->imgd.sdat.line_length;
		vars->config.sprs[spr].spt.endian = vars->imgd.sdat.endian;
		spr++;
	}
}
