/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:50:29 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/12 17:44:12 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3		raycast(t_scene *scene, t_ray ray);
t_object	*find_closest_obj(t_scene *scene, t_ray ray, double *out_t);

static t_vec3	get_normal(t_object *obj, t_vec3 hit_point, t_vec3 ray_dir)
{
	t_vec3	normal;

	if (obj->type == SPHERE)
		normal = vec3_normalize(vec3_sub(hit_point, obj->curr.pos));
	else if (obj->type == PLANE)
	{
		normal = obj->curr.normal;
		if (vec3_dot(normal, ray_dir) > 0)
			normal = vec3_scale(normal, -1.0);
	}
	else if (obj->type == CYLINDER)
		normal = obj->curr.normal;
	else
		normal = vec3_init(0, 1, 0);
	return (normal);
}

// レンダリング
void	render_scene(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_vec3	pixel_color;

	update_camera(scene->cam);
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
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win,
		scene->mlx->img, 0, 0);
}

// レイが光が当たるかどうか。環境光、ライティング、影の計算を行う
t_vec3	raycast(t_scene *scene, t_ray ray)
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
		rec.color = closest_obj->color;
		rec.t = min_t;
		rec.hit = 1;
		color = calc_lighting(scene->objs, scene->amb, scene->ligs, &rec);
		return (color);
	}
	return (vec3_init(0.1, 0.1, 0.1));
}

// カメラから近いオブジェクトを判定
t_object	*find_closest_obj(t_scene *scene, t_ray ray, double *out_t)
{
	t_object	*curr;
	t_object	*closest_obj;
	double		min_t;
	double		t;

	curr = scene->objs;
	closest_obj = NULL;
	min_t = INFINITY;
	while (curr)
	{
		t = -1.0;
		if (curr->type == SPHERE)
			t = hit_sphere(curr, ray);
		else if (curr->type == CYLINDER)
			t = hit_cylinder(curr, ray);
		else if (curr->type == PLANE)
			t = hit_plane(curr, ray);
		// 0より大きく、かつこれまでの最小距離より近い場合のみ更新
		if (t > EPSILON && t < min_t)
		{
			min_t = t;
			closest_obj = curr;
		}
		curr = curr->next;
	}
	*out_t = min_t;
	return (closest_obj);
}
