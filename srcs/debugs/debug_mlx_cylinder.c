/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mlx_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:24:01 by hayato            #+#    #+#             */
/*   Updated: 2026/02/10 06:57:47 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** 固定カメラ・固定球での描画テスト
** 交差したら赤、しなかったら青
*/void    render_test(t_mlx *mlx, int width, int height)
{
    t_object    obj;
    t_ray       ray;
	t_camera	cam;
    double      t;
    int         color;
    int         px;
    int         py;

    // 円柱の設定
    obj.type = CYLINDER;
    obj.position = vec3_init(0, -1, 0);          // 底面の中心
    obj.data.cy.normal = vec3_normalize(vec3_init(0, 1, 0)); // 少し傾ける
    obj.data.cy.radius = 1.0;
    obj.data.cy.height = 2.0;
	cam.init_pos = vec3_init(2.0, 3.0, -5.0);
	cam.init_dir = vec3_init(0.0, 0.0, 1.0);
	cam.fov = 60;
	cam.pos = cam.init_pos;
	cam.dir = cam.init_dir;
	cam.pitch = 25 * (M_PI / 180.0); // カメラが下を向く
	cam.yaw = -45 * (M_PI/ 180.0); // カメラが左に向く

	update_camera(&cam);

    py = 0;
    while (py < height)
    {
        px = 0;
        while (px < width)
        {
            ray = get_ray(px, py, &cam); // カメラからのレイを取得

            //  円柱の呼び出し
            t = hit_cylinder(&obj, ray);

            if (t > 0)
                color = 0xFF0000; // ヒットしたら赤
            else
                color = 0x0000FF; // 背景は青

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
