#include "miniRT.h"

/*
** 影（シャドウ）のデバッグ
** 複数オブジェクトがある場面で影の描画をテスト
**
** 使用する関数:
** - is_in_shadow (shadow.c)
** - calc_lighting (calc_shading.c)
*/

/*
** 球体の法線ベクトルを計算
*/
static t_vec3	get_sphere_normal(t_vec3 hit_point, t_vec3 sphere_center)
{
	return (vec3_normalize(vec3_sub(hit_point, sphere_center)));
}

/*
** 平面の法線ベクトルを取得（構造体から）
*/
static t_vec3	get_plane_normal(t_object *obj, t_vec3 ray_dir)
{
	t_vec3	normal;

	normal = obj->data.pl.normal;
	/* レイの方向と法線が同じ向きなら反転 */
	if (vec3_dot(normal, ray_dir) > 0)
		normal = vec3_scale(normal, -1.0);
	return (normal);
}

/*
** 最も近い交差を見つける
*/
static int	find_closest_hit(t_object *objects, t_ray ray, t_hit_record *rec)
{
	t_object	*obj;
	t_object	*closest_obj;
	double		t;
	double		closest_t;

	closest_t = 1e30;
	closest_obj = NULL;
	obj = objects;
	while (obj)
	{
		t = -1;
		if (obj->type == SPHERE)
			t = hit_sphere(obj, ray);
		else if (obj->type == PLANE)
			t = hit_plane(obj, ray);
		if (t > 0.0001 && t < closest_t)
		{
			closest_t = t;
			closest_obj = obj;
		}
		obj = obj->next;
	}
	if (!closest_obj)
	{
		rec->hit = 0;
		return (0);
	}
	rec->t = closest_t;
	rec->point = ray_at(ray, closest_t);
	rec->color = closest_obj->color;
	rec->hit = 1;
	if (closest_obj->type == SPHERE)
		rec->normal = get_sphere_normal(rec->point, closest_obj->curr.pos);
	else if (closest_obj->type == PLANE)
		rec->normal = get_plane_normal(closest_obj, ray.direction);
	return (1);
}

/*
** レンダリングテスト
*/
static void	render_shadow_test(t_mlx *mlx, t_scene *scene,
		int width, int height)
{
	t_ray			ray;
	t_hit_record	rec;
	t_vec3			color;
	int				px;
	int				py;

	py = 0;
	while (py < height)
	{
		px = 0;
		while (px < width)
		{
			ray = get_ray_fixed(px, py);
			if (find_closest_hit(scene->objs, ray, &rec))
			{
				/* calc_lighting で影を考慮したシェーディングを計算 */
				color = calc_lighting(scene->objs, scene->amb,
						scene->ligs, &rec);
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
	/* rtファイルの指定（デフォルト: rtfiles/shadow_test.rt） */
	if (argc >= 2)
		rt_file = argv[1];
	else
		rt_file = "rtfiles/shadow_test.rt";
	/* シーンデータの読み込み */
	if (rt_loader(&scene, rt_file) != 0)
	{
		printf("Error: rtファイルの読み込みに失敗: %s\n", rt_file);
		return (1);
	}
	printf("=== Shadow Debug ===\n");
	printf("Loaded: %s\n", rt_file);
	printf("Objects: sphere + plane\n");
	printf("Shadow: enabled\n");
	/* MiniLibXの初期化 */
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"MiniRT Debug Shadow");
	mlx.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
			&mlx.line_length, &mlx.endian);
	/* レンダリングテスト */
	render_shadow_test(&mlx, &scene, WIN_WIDTH, WIN_HEIGHT);
	/* 画像をウィンドウに表示 */
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	/* イベントループ開始 */
	mlx_key_hook(mlx.win, key_hook, &scene);
	mlx_hook(mlx.win, EVENT_CLOSE, 0, close_window, &scene);
	mlx_loop(mlx.mlx);
	free_scene(&scene);
	return (0);
}
