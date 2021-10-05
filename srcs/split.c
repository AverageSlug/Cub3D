/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 12:51:20 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 17:58:02 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*cub3d_fill(char const *s, int min, int max)
{
	char	*fill;
	int		q;
	int		r;

	r = 0;
	q = max - min;
	if (!(fill = malloc(sizeof(char) * (q + 1))))
		return (NULL);
	while (min < max)
	{
		fill[r] = s[min];
		min++;
		r++;
	}
	fill[r] = '\0';
	return (fill);
}

static void	cub3d_text(char const *s, char c, int i, char **ret)
{
	int m;
	int n;

	m = 0;
	n = 0;
	while (s[++i])
		if (s[i] == c || !(s[i + 1]))
		{
			if (!(s[i + 1]) && !(s[i] == c))
				ret[n++] = cub3d_fill(s, i - m, i + 1);
			else if (m > 0)
				ret[n++] = cub3d_fill(s, i - m, i);
			if (n != 0 && !(ret[n - 1]))
			{
				while (n - 1)
					free(ret[--n - 1]);
				return ;
			}
			m = 0;
		}
		else
			m++;
	ret[n] = NULL;
}

static int	cub3d_splitlen(char const *s, char c)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c || !(s[i + 1]))
		{
			if (!(s[i + 1] && s[i] == c))
				j++;
			if (j > 0)
				k++;
			j = 0;
		}
		else
			j++;
		i++;
	}
	return (k);
}

char		**cub3d_split(char const *s, char c)
{
	int		splitlen;
	char	**ret;
	int		i;

	if (!s)
		return (NULL);
	splitlen = cub3d_splitlen(s, c);
	if (!(ret = malloc(sizeof(char*) * (splitlen + 1))))
		return (NULL);
	i = -1;
	cub3d_text(s, c, i, ret);
	return (ret);
}
