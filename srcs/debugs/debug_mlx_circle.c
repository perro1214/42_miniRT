/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mlx_circle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:24:01 by hayato            #+#    #+#             */
/*   Updated: 2026/02/10 02:32:13 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** 固定カメラ・固定球での描画テスト
** 交差したら赤、しなかったら青
*/
void    render_test(t_mlx *mlx, int width, int height)
{
    t_object    obj;
    t_ray       ray;
    double      t;
    int         color;
    int         px;
    int         py;

    // 円（CIRCLE）の設定
    obj.type = CIRCLE;
    obj.pos = vec3_init(0, 0, 5);              // 中心座標
    obj.curr.pos = obj.pos;
    obj.data.ci.normal = vec3_normalize(vec3_init(0, 1, 1)); // 斜め45度に向ける
    obj.curr.normal = obj.data.ci.normal;
    obj.data.ci.radius = 1.5f;

    py = 0;
    while (py < height)
    {
        px = 0;
        while (px < width)
        {
            ray = get_ray_fixed(px, py); // カメラからのレイを取得

            // 統合した hit_circle を呼び出し
            t = hit_circle(&obj, ray);

            if (t > 0)
                color = 0xFF0000; // ヒットしたら白
            else
                color = 0x0000FF; // 背景は黒

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
