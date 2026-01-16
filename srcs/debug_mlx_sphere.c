/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mlx_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:24:01 by hayato            #+#    #+#             */
/*   Updated: 2026/01/13 22:54:12 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** 固定カメラ・固定球での描画テスト
** 交差したら赤、しなかったら青
*/
void	render_test(t_mlx *mlx, int width, int height)
{
	t_sphere	sp;
	t_ray		ray;
	double		t;
	int			color;

	int px, py;
	// テスト用の球
	sp.center = vec3_init(0, 0, 5);
	sp.radius = 1.0;
	py = 0;
	while (py < height)
	{
		px = 0;
		while (px < width)
		{
			ray = get_ray_fixed(px, py);
			t = hit_sphere(&sp, ray);
			if (t > 0)
				color = 0xFF0000; // 赤（交差あり）
			else
				color = 0x0000FF; // 青（交差なし）
			ft_mlx_put_pixel(mlx, px, py, color);
			px++;
		}
		py++;
	}
}

int	main(int argc, char **argv){
	t_mlx	mlx;

	(void)argc;
	(void)argv;
	// MiniLibXの初期化
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "MiniRT Debug Sphere");
	mlx.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	// レンダリングテスト
	render_test(&mlx, WIN_WIDTH, WIN_HEIGHT);
	// 画像をウィンドウに表示
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	// イベントループ開始
	mlx_loop(mlx.mlx);
	return (0);
}
