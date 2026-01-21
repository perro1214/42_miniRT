/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:38:56 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/21 23:47:32 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#ifndef EPSILON
# define EPSILON 1e-8
#endif


static int	is_valid_double_str(char *str);

// ヘルパー関数(文字列を、vec3に変換とエラーチェック）
t_vec3	str_to_vec3(char *str, int *status)
{
	char	**tab;
	t_vec3	vec;
	int		i;

	vec = vec3_init(0, 0, 0);
	tab = ft_split(str, ',');
	if (!tab || ft_count_tab(tab) != 3)
	{
		*status = 1;
		return (ft_free_tab(tab), vec);
	}
	i = -1;
	while (++i < 3)
	{
		if (!is_valid_double_str(tab[i]))
		{
			*status = 1;
			return (ft_free_tab(tab), vec);
		}
	}
	vec = vec3_init(atof(tab[0]), atof(tab[1]), atof(tab[2]));
	ft_free_tab(tab);
	*status = 0;
	return (vec);
}


// 範囲チェック
int	is_in_range(double value, double min, double max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

// 正規化できるかどうかをチェック、0,0,0もはじく
int	is_normalized(t_vec3 vec)
{
	double	mag_sq;

	mag_sq = (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
	if (mag_sq < (1.0 - EPSILON) || mag_sq > (1.0 + EPSILON))
		return (0);
	return (1);
}

/*
 * 文字列が [0-9], '.', '+', '-' だけで構成されているか
 * かつ、ドットが2つ以上ないかをチェック
 */
static int	is_valid_double_str(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (++dot_count > 1)
				return (0);
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

double get_double(char *str, int *status)
{
	if (!str || !is_valid_double_str(str))
	{
		*status = 1;
		return (0.0);
	}
	return (atof(str));
}
