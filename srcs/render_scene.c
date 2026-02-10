/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:50:29 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/10 15:29:14 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


t_vec3		raycast(t_scene *scene, t_ray ray);
t_object	*find_closest_obj(t_scene *scene, t_ray ray, double *out_t);

// レンダリング
void	render_scene(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_vec3	pixel_color;
	t_vec3	color_255;

	update_camera(scene->cam);
	y = 0;
	while ( y < WIN_HEIGHT)
	{
		x = 0;
		while ( x < WIN_WIDTH)
		{
			ray = get_ray(x, y, scene->cam);
			pixel_color = raycast(scene, ray);
			color_255 = denormalize_color(clamp_color(pixel_color));
			ft_mlx_put_pixel(scene->mlx, x, y, vec3_to_color(color_255));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img, 0, 0);
}

// レイが光が当たるかどうか。
t_vec3	raycast(t_scene *scene, t_ray ray)
{
	t_object	*closest_obj;
	double		min_t;

	closest_obj = find_closest_obj(scene, ray, &min_t);
	if (closest_obj)
	{
		// この辺に、環境光、ライティング、影の計算を開始 ->計算したカラーをリターン
		return (closest_obj->color); // 当たった物体の色
	}
	return (vec3_init(0.1, 0.1, 0.1)); // 背景色
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
