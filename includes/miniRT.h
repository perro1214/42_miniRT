/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:27:40 by hayato            #+#    #+#             */
/*   Updated: 2026/01/13 23:03:12 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include "ray.h"
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
}			t_mlx;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_color	color;
}			t_sphere;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	double	fov;
}			t_camera;

typedef struct s_ambient
{
	double	ratio;

	t_color	color;

}			t_ambient;

typedef struct s_light
{
	t_vec3	position;
	double	intensity;
	t_color	color;
}			t_light;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}			t_plane;

// mlx_action_close.c
int			key_hook(int keycode, t_mlx *mlx);
int			close_window(t_mlx *mlx);

// render_pixel.c
void		ft_mlx_put_pixel(t_mlx *mlx, int x, int y, int color);
t_color		color_init(int r, int g, int b);
t_color		color_multiply(t_color color_A, t_color color_B);
t_color		color_scalar(t_color color, float scalar);
int			create_color(t_color color);

// error.c
void		log_error(char *message);

// arg_parser.c
int			parse_arguments(int argc, char **argv);

// timer.c
double		current_time_ms(void);
void		log_elapsed_time(double start_time);

// hit_sphere.c
double		hit_sphere(t_sphere *sphere, t_ray ray);

// hit_plane.c
double		hit_plane(t_plane *plane, t_ray ray);

// screen_norm.c
t_ray		get_ray_fixed(int px, int py);

#endif // MINIRT_H
