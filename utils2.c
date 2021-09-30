/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:18:35 by nlaurids          #+#    #+#             */
/*   Updated: 2020/10/19 16:50:04 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		tex_color_get(t_data *data, int x, int y)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	cub3d_set_ac(char ac[256], char tile, int j, int mxs)
{
	int t;

	t = -1;
	while (++t <= 255)
		ac[t] = 0;
	ac[' '] = 1;
	ac['0'] = 1;
	ac['1'] = 1;
	ac['2'] = 1;
	ac['N'] = 1;
	ac['E'] = 1;
	ac['W'] = 1;
	ac['S'] = 1;
	if (tile == ' ' || tile == 0 || j >= mxs)
	{
		ac['0'] = 0;
		ac['2'] = 0;
		ac['N'] = 0;
		ac['E'] = 0;
		ac['W'] = 0;
		ac['S'] = 0;
	}
	else if (tile == '0' || tile == '2' ||
			tile == 'N' || tile == 'E' || tile == 'W' || tile == 'S')
		ac[' '] = 0;
}

void	cub3d_set_mxs(int mxs[3], char **map, int i)
{
	mxs[1] = ft_strlen(map[i - 1]);
	mxs[2] = ft_strlen(map[i + 1]);
	if (mxs[1] < mxs[2])
		mxs[0] = mxs[1];
	else
		mxs[0] = mxs[2];
}
