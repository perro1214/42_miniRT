/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:32:10 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/21 22:34:37 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// カラー範囲のチェック
int	is_valid_color(t_vec3 color)
{
	if (color.x < 0.0 || color.x > 255.0)
		return (0);
	if (color.y < 0.0 || color.y > 255.0)
		return (0);
	if (color.z < 0.0 || color.z > 255.0)
		return (0);
	return (1);
}
