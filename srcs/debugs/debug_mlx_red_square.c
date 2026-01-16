/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mlx_red_square.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:30:11 by hayato            #+#    #+#             */
/*   Updated: 2026/01/13 21:10:02 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	diff_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2)
	{
		ft_putendl_fd("Error: Invalid number of arguments.", 2);
		return (1);
	}
	printf("Sorce file: %s\n", argv[1]);
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
	{
		ft_putendl_fd("Error: mlx_init failed.", 2);
		return (1);
	}
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!mlx.win)
	{
		ft_putendl_fd("Error: mlx_new_window failed.", 2);
		return (1);
	}
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_hook(mlx.win, EVENT_CLOSE, 0, close_window, &mlx);
	// 画像バッファ作成
	mlx.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
			&mlx.endian);


	// 赤い四角を描画
	t_vec3 red = vec3_init(255, 0, 0);
	for (int y = 100; y < 200; y++)
	{
		for (int x = 100; x < 200; x++)
		{
			ft_mlx_put_pixel(&mlx, x, y, vec3_to_color(red));
		}
	}

	t_vec3 white = vec3_init(255, 255, 255);
	// 色の混合: (r1 * r2) / 255
	t_vec3 red_white;
	red_white.x = (red.x * white.x) / 255.0f;
	red_white.y = (red.y * white.y) / 255.0f;
	red_white.z = (red.z * white.z) / 255.0f;
	printf("Red-White Mixed Color: R=%.0f, G=%.0f, B=%.0f\n", red_white.x, red_white.y, red_white.z);

	for (int y = 250; y < 350; y++)
	{
		for (int x = 250; x < 350; x++)
		{
			ft_mlx_put_pixel(&mlx, x, y, vec3_to_color(red_white));
		}
	}

	
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
