/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:30:11 by hayato            #+#    #+#             */
/*   Updated: 2026/02/16 23:41:51 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_mlx(t_mlx *mlx, t_scene *scene)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (log_error("mlx_init failed."), 1);
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!mlx->win)
		return (log_error("mlx_new_window failed."), 1);
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img)
		return (log_error("mlx_new_image failed."), 1);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	scene->mlx = mlx;
	return (0);
}

static void	set_mlx_hooks(t_mlx *mlx, t_scene *scene)
{
	mlx_key_hook(mlx->win, key_hook, scene);
	mlx_mouse_hook(mlx->win, mouse_hook, scene);
	mlx_expose_hook(mlx->win, expose_hook, scene);
	mlx_hook(mlx->win, EVENT_CLOSE, 0, close_window, scene);
	mlx_loop_hook(mlx->mlx, loop_hook, scene);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_scene	scene;

	if (parse_arguments(argc, argv))
		return (1);
	ft_memset(&scene, 0, sizeof(t_scene));
	if (rt_loader(&scene, argv[1]) != 0 || is_valid_scene(&scene) != 0)
	{
		free_scene(&scene);
		return (1);
	}
	if (init_mlx(&mlx, &scene) != 0)
	{
		free_scene(&scene);
		return (1);
	}
	show_manual();
	render_scene(&scene);
	set_mlx_hooks(&mlx, &scene);
	mlx_loop(mlx.mlx);
	free_scene(&scene);
	return (0);
}
