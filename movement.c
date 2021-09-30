/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:19:04 by nlaurids          #+#    #+#             */
/*   Updated: 2020/10/19 13:23:02 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mv_hor(t_vars *vars)
{
	if (vars->key.mv_hor)
	{
		if (vars->config.map[(int)(vars->sdir.posx + vars->sdir.diry *
				vars->mov * vars->key.mv_hor + vars->pluy * vars->key.mv_hor)]
				[(int)(vars->sdir.posy + vars->plux)] != '1' &&
				vars->config.map[(int)(vars->sdir.posx + vars->sdir.diry *
				vars->mov * vars->key.mv_hor + vars->pluy * vars->key.mv_hor)]
				[(int)(vars->sdir.posy - vars->plux)] != '1')
			vars->sdir.posx += vars->sdir.diry * vars->mov * vars->key.mv_hor;
		if (vars->config.map[(int)(vars->sdir.posx + vars->plux)]
				[(int)(vars->sdir.posy - vars->sdir.dirx * vars->mov *
				vars->key.mv_hor - vars->plux * vars->key.mv_hor)] != '1' &&
				vars->config.map[(int)(vars->sdir.posx - vars->plux)]
				[(int)(vars->sdir.posy - vars->sdir.dirx * vars->mov *
				vars->key.mv_hor - vars->plux * vars->key.mv_hor)] != '1')
			vars->sdir.posy -= vars->sdir.dirx * vars->mov * vars->key.mv_hor;
	}
}

void	mv_ver(t_vars *vars)
{
	if (vars->key.mv_ver)
	{
		if (vars->config.map[(int)(vars->sdir.posx + vars->plux)]
				[(int)(vars->sdir.posy - vars->sdir.diry * vars->mov *
				vars->key.mv_ver - vars->pluy * vars->key.mv_ver)] != '1' &&
				vars->config.map[(int)(vars->sdir.posx - vars->plux)]
				[(int)(vars->sdir.posy - vars->sdir.diry * vars->mov *
				vars->key.mv_ver - vars->pluy * vars->key.mv_ver)] != '1')
			vars->sdir.posy -= vars->sdir.diry * vars->mov * vars->key.mv_ver;
		if (vars->config.map[(int)(vars->sdir.posx - vars->sdir.dirx *
				vars->mov * vars->key.mv_ver - vars->plux * vars->key.mv_ver)]
				[(int)(vars->sdir.posy + vars->plux)] != '1' &&
				vars->config.map[(int)(vars->sdir.posx - vars->sdir.dirx *
				vars->mov * vars->key.mv_ver - vars->plux * vars->key.mv_ver)]
				[(int)(vars->sdir.posy - vars->plux)] != '1')
			vars->sdir.posx -= vars->sdir.dirx * vars->mov * vars->key.mv_ver;
	}
}

void	look(t_vars *vars)
{
	double temp;

	if (vars->key.look)
	{
		vars->rot *= vars->key.look;
		temp = vars->sdir.dirx;
		vars->sdir.dirx = vars->sdir.dirx * cos(vars->rot * (-1)) -
				vars->sdir.diry * sin(vars->rot * (-1));
		vars->sdir.diry = temp * sin(vars->rot * (-1)) +
				vars->sdir.diry * cos(vars->rot * (-1));
		temp = vars->sdir.plnx;
		vars->sdir.plnx = vars->sdir.plnx * cos(vars->rot * (-1)) -
				vars->sdir.plny * sin(vars->rot * (-1));
		vars->sdir.plny = temp * sin(vars->rot * (-1)) +
				vars->sdir.plny * cos(vars->rot * (-1));
	}
}
