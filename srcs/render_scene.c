/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:50:29 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/16 05:25:14 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3		raycast(t_scene *scene, t_ray ray);
t_object	*find_closest_obj(t_scene *scene, t_ray ray, double *out_t);
t_vec3		get_cylinder_normal(t_object *obj, t_vec3 hit_point);
t_vec3		get_cone_normal(t_object *obj, t_vec3 hit_point);

static t_vec3	get_normal(t_object *obj, t_vec3 hit_point, t_vec3 ray_dir)
{
	t_vec3	normal;

	// オブジェクトの数学的な外向きの法線を算出
	if (obj->type == SPHERE)
		normal = vec3_normalize(vec3_sub(hit_point, obj->curr.pos));
	else if (obj->type == PLANE)
		normal = obj->curr.normal;
	else if (obj->type == CYLINDER)
		normal = get_cylinder_normal(obj, hit_point);
	else if (obj->type == CONE)
		normal = get_cone_normal(obj, hit_point);
	else
		normal = vec3_init(0, 1, 0);
	// 内積が正 = 同じ方向を向いている
	// レイの方向と反対を向くように調整する
	if (vec3_dot(ray_dir, normal) > 0)
		return (vec3_scale(normal, -1.0)); // 方向を判定
	return (normal);
}

// 円柱の法線を求める
t_vec3 get_cylinder_normal(t_object *obj, t_vec3 hit_point)
{
	t_vec3	cp;
	double	m;
	t_vec3	q;
	// 円柱の底面から交点へのベクトル
	cp = vec3_sub(hit_point, obj->curr.pos);
	// 交点が軸のどの高さに対応するか計算
	m = vec3_dot(cp, obj->curr.normal);

	// 蓋に当たった場合
	if (m <= EPSILON)
		return (vec3_scale(obj->curr.normal, -1.0)); // 底面下向きにする
	if (m >= obj->data.cy.height - EPSILON)
		return (obj->curr.normal); // 上面は上向き

	// 側面に当たった場合
	// 法線 = 交点 - 軸上の対応する点
	q = vec3_scale(obj->curr.normal, m);
	return (vec3_normalize(vec3_sub(cp, q)));
}

// 円錐の法線を求める
// 頂点から交点へのベクトル V​= P - tip
// 軸方向のベクトル N = V​−(1+k^2)・m・normal
t_vec3 get_cone_normal(t_object *obj, t_vec3 hit_point)
{
	t_vec3	cp;
	t_vec3	tip;
	t_vec3	v;
	double 	h;
	double	m;
	t_vec3	n;

	// 円柱の底面から交点へのベクトル
	cp = vec3_sub(hit_point, obj->curr.pos);
	m = vec3_dot(cp, obj->curr.normal);
	// 蓋（底面）に当たった場合
    // 高さがほぼ0なら底面。法線は軸の逆向き。
    if (m <= EPSILON)
        return (vec3_scale(obj->curr.normal, -1.0));
	// 側面に当たった場合
	tip = vec3_add(obj->curr.pos, vec3_scale(obj->curr.normal, obj->data.co.height));
	// 頂点から交点へのベクトル
	v = vec3_sub(hit_point, tip);
	// 軸方向の距離
	h = vec3_dot(v, obj->curr.normal);
	n = vec3_sub(v, vec3_scale(obj->curr.normal, (1.0 + obj->data.co.k_sq) * h));
	return (vec3_normalize(n));
}


// レンダリング
void	render_scene(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_vec3	pixel_color;

	//update_camera(scene->cam);
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
		else if (curr->type == CONE)
			t = hit_cone(curr, ray);
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

