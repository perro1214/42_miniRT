/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:27:40 by hayato            #+#    #+#             */
/*   Updated: 2026/01/13 17:49:36 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include "vec3.h"
# include <stdio.h>

// Window size
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// Keycode
# define KEY_ESCAPE 65307

// Event code
# define EVENT_CLOSE 17

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_color	color;
}	t_sphere;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	double	fov;
}	t_camera;

// mlx_action_close.c
int		key_hook(int keycode, t_mlx *mlx);
int		close_window(t_mlx *mlx);

// render_pixel.c
void	ft_mlx_put_pixel(t_mlx *mlx, int x, int y, int color);
int		create_color(int r, int g, int b);

// error.c
void	log_error(char *message);

// arg_parser.c
int		parse_arguments(int argc, char **argv);

// timer.c
double	current_time_ms();
void	log_elapsed_time(double start_time);

#endif // MINIRT_H
