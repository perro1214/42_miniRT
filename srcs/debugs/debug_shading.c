/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_shading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:00:00 by hayato            #+#    #+#             */
/*   Updated: 2026/01/16 00:00:00 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** シェーディング（環境光＋拡散反射）のデバッグ
** 球体に光を当てて、シェーディングの結果を視覚的に確認する
**
** 使用する関数（他ファイルで実装済み）:
** - color_to_unit, denormalize_color, clamp_color (color_util.c)
** - calc_ambient (calc_ambient.c)
** - calc_diffuse (calc_diffuse.c)
** - calc_shading (calc_shading.c)
*/

/*
** 球体の法線ベクトルを計算（交点から球心を引いて正規化）
*/
static t_vec3	get_sphere_normal(t_vec3 hit_point, t_vec3 sphere_center)
{
	return (vec3_normalize(vec3_sub(hit_point, sphere_center)));
}

/*
** レンダリングテスト
** rtファイルから読み込んだシーンデータでシェーディングをテスト
*/
static void	render_shading_test(t_mlx *mlx, t_scene *scene,
		int width, int height)
{
	t_object		*obj;
	t_ray			ray;
	double			t;
	t_hit_record	rec;
	t_vec3			color;
	int				px;
	int				py;

	obj = scene->objs;
	py = 0;
	while (py < height)
	{
		px = 0;
		while (px < width)
		{
			ray = get_ray_fixed(px, py);
			t = hit_sphere(obj, ray);
			if (t > 0)
			{
				/* 交差情報をセット */
				rec.point = ray_at(ray, t);
				rec.normal = get_sphere_normal(rec.point, obj->curr.pos);
				rec.color = obj->color;
				rec.t = t;
				rec.hit = 1;
				/* calc_shading を呼び出し */
				color = calc_shading(&rec, scene->amb, scene->ligs);
				ft_mlx_put_pixel(mlx, px, py, vec3_to_color(color));
			}
			else
			{
				/* 背景色（暗い青） */
				ft_mlx_put_pixel(mlx, px, py, 0x001020);
			}
			px++;
		}
		py++;
	}
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_scene	scene;
	char	*rt_file;

	scene.mlx = &mlx;
	scene.cam = NULL;
	scene.amb = NULL;
	scene.ligs = NULL;
	scene.objs = NULL;
	scene.selected_obj = NULL;
	/* rtファイルの指定（デフォルト: rtfiles/sphere.rt） */
	if (argc >= 2)
		rt_file = argv[1];
	else
		rt_file = "rtfiles/sphere.rt";
	/* シーンデータの読み込み */
	if (rt_loader(&scene, rt_file) != 0)
	{
		printf("Error: rtファイルの読み込みに失敗: %s\n", rt_file);
		return (1);
	}
	printf("=== Shading Debug ===\n");
	printf("Loaded: %s\n", rt_file);
	/* MiniLibXの初期化 */
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"MiniRT Debug Shading");
	mlx.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
			&mlx.line_length, &mlx.endian);
	/* レンダリングテスト */
	render_shading_test(&mlx, &scene, WIN_WIDTH, WIN_HEIGHT);
	/* 画像をウィンドウに表示 */
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	/* イベントループ開始 */
	mlx_key_hook(mlx.win, key_hook, &scene);
	mlx_hook(mlx.win, EVENT_CLOSE, 0, close_window, &scene);
	mlx_loop(mlx.mlx);
	free_scene(&scene);
	return (0);
}
