/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:30:11 by hayato            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/13 19:07:32 by htsutsum         ###   ########.fr       */
=======
/*   Updated: 2026/01/13 17:46:21 by hayato           ###   ########.fr       */
>>>>>>> origin
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (parse_arguments(argc, argv))
		return (1);
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
	mlx_loop(mlx.mlx);
	return (0);
}
