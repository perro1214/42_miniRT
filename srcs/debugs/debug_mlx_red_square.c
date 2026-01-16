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
	t_color red = color_init(255, 0, 0);
	for (int y = 100; y < 200; y++)
	{
		for (int x = 100; x < 200; x++)
		{
			ft_mlx_put_pixel(&mlx, x, y, create_color(red));
		}
	}

	t_color white = color_init(255, 255, 255);
	t_color red_white = color_multiply(red, white);
	printf("Red-White Mixed Color: R=%d, G=%d, B=%d\n", red_white.r, red_white.g, red_white.b);

	for (int y = 250; y < 350; y++)
	{
		for (int x = 250; x < 350; x++)
		{
			ft_mlx_put_pixel(&mlx, x, y, create_color(red_white));
		}
	}

	
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
