/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:30:11 by hayato            #+#    #+#             */
/*   Updated: 2026/01/15 00:37:17 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	if (parse_arguments(argc, argv))
		return (1);
	printf("Source file: %s\n", argv[1]);
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
	{
		log_error("mlx_init failed.");
		return (1);
	}
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!mlx.win)
	{
		log_error("mlx_new_window failed.");
		return (1);
	}
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_hook(mlx.win, EVENT_CLOSE, 0, close_window, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
