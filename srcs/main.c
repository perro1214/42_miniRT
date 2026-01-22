/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:30:11 by hayato            #+#    #+#             */
/*   Updated: 2026/01/22 00:53:14 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_scene	scene;

	if (parse_arguments(argc, argv))
		return (1);

	ft_memset(&scene, 0 ,sizeof(t_scene));
	printf("Source file: %s\n", argv[1]);
	if (rt_loader(&scene, argv[1]) != 0 || is_valid_scene(&scene) != 0)
    {
        free_scene(&scene);
        return (1);
	}
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
	{
		free_scene(&scene);
		log_error("mlx_init failed.");
		return (1);
	}
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!mlx.win)
	{
		free_scene(&scene);
		log_error("mlx_new_window failed.");
		return (1);
	}
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_hook(mlx.win, EVENT_CLOSE, 0, close_window, &mlx);
	mlx_loop(mlx.mlx);
	free_scene(&scene);
	return (0);
}
