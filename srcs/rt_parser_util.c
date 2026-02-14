/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:38:56 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/15 06:20:10 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

//ヘルパー関数(文字のチェックした後に値を返す）
double	get_double(char *str, int *status)
{
	if (!str || !is_valid_double_str(str))
	{
		*status = 1;
		return (0.0);
	}
	return (atof(str));
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

// checker_flag 0か１か判定
int is_valid_checker_flag(char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) != 1)
		return (0);
	if (*str == '0' || *str == '1')
		return (1);
	return (0);
}
