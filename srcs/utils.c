/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:36:07 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 17:58:07 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		cub3d_atoi(const char *str)
{
	unsigned long long	p;
	int					boo;

	p = 0;
	boo = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f' ||
			*str == '\r' || *str == ' ')
		str++;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str++ == '-')
			boo = -1;
	}
	while (*str >= 48 && *str <= 57)
	{
		if (p > 9223372036854775807)
		{
			if (boo == -1)
				return (0);
			else
				return (-1);
		}
		p = p * 10 + (*str++ - 48);
	}
	return (p * boo);
}

int		cub3d_realloc(char **tem, char *line, int size, t_conf *config)
{
	int i;

	i = -1;
	if (!(config->map = malloc(sizeof(char*) * (size + 2))))
		return (0);
	while (++i < size)
		config->map[i] = tem[i];
	if (!(config->map[size] = cub3d_strdup(line)))
		return (0);
	config->map[size + 1] = 0;
	if (tem)
		free(tem);
	return (1);
}

char	*cub3d_strdup(const char *s1)
{
	int		num;
	char	*s1s1;

	num = ft_strlen(s1);
	if (!(s1s1 = malloc(sizeof(char) * num + 1)))
		return (0);
	num = 0;
	while (*s1)
		s1s1[num++] = *s1++;
	s1s1[num] = '\0';
	return (s1s1);
}

void	freerealine(char **realine)
{
	int	i;

	i = 0;
	while (realine[i])
	{
		free(realine[i]);
		realine[i++] = NULL;
	}
	free(realine);
	realine = NULL;
}

int		ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
