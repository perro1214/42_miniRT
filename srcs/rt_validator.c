/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_validator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:32:10 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/16 23:54:41 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_in_range(double value, double min, double max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

int	is_valid_color(t_vec3 color)
{
	if (!is_in_range(color.x, 0.0, 255.0))
		return (0);
	if (!is_in_range(color.y, 0.0, 255.0))
		return (0);
	if (!is_in_range(color.z, 0.0, 255.0))
		return (0);
	return (1);
}

int	is_valid_normal(t_vec3 normal)
{
	if (!is_in_range(normal.x, -1.0, 1.0))
		return (0);
	if (!is_in_range(normal.y, -1.0, 1.0))
		return (0);
	if (!is_in_range(normal.z, -1.0, 1.0))
		return (0);
	if (normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0)
		return (0);
	return (1);
}

int	is_normalized(t_vec3 vec)
{
	double	mag_sq;

	mag_sq = (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
	if (mag_sq < (1.0 - EPSILON) || mag_sq > (1.0 + EPSILON))
		return (0);
	return (1);
}

int	is_valid_normal_vec(t_vec3 normal)
{
	if (!is_valid_normal(normal))
		return (0);
	if (!is_normalized(normal))
		return (0);
	return (1);
}
