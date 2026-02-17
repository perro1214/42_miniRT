/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:50:29 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/17 04:24:39 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void		ft_mlx_put_pixel(t_mlx *mlx, int x, int y, int color);
static t_vec3	raycast(t_scene *scene, t_ray ray);

void	render_scene(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_vec3	pixel_color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray = get_ray(x, y, scene->cam);
			pixel_color = raycast(scene, ray);
			ft_mlx_put_pixel(scene->mlx, x, y, vec3_to_color(pixel_color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img,
		0, 0);
}

static void	ft_mlx_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel >> 3));
	*(unsigned int *)dst = color;
}

static t_vec3	raycast(t_scene *scene, t_ray ray)
{
	t_object		*closest_obj;
	double			min_t;
	t_hit_record	rec;
	t_vec3			color;

	closest_obj = find_closest_obj(scene, ray, &min_t);
	if (closest_obj)
	{
		rec.point = ray_at(ray, min_t);
		rec.normal = get_normal(closest_obj, rec.point, ray.direction);
		rec.view_dir = vec3_normalize(vec3_scale(ray.direction, -1.0));
		rec.t = min_t;
		rec.hit = 1;
		if (closest_obj->type == PLANE && closest_obj->data.pl.checker_flag)
			rec.color = get_checker_color(&rec, closest_obj);
		else
			rec.color = closest_obj->color;
		color = calc_lighting(scene->objs, scene->amb, scene->ligs, &rec);
		return (color);
	}
	return (vec3_init(0.1, 0.1, 0.1));
}
