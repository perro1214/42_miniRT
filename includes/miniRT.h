/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:27:40 by hayato            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/14 01:57:12 by htsutsum         ###   ########.fr       */
=======
/*   Updated: 2026/01/13 17:49:36 by hayato           ###   ########.fr       */
>>>>>>> origin
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "get_next_line.h"
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

typedef enum e_type {
    SPHERE,
    PLANE,
    CYLINDER
} t_type;

typedef union  u_obj_data {
    t_sphere sp;
    t_plane pl;
    t_cylinder cu;
} t_obj_data;

typedef struct s_object {
    int			type;
    t_vec3		center;
    t_color		color;
    t_obj_data	data;
}t_object;

typedef struct	s_plane
{
 	t_vec3	normal;  // 平面の法線ベクトル
}	t_plane;

typedef struct	s_sphere
{
 	double	radius; // 球の半径 （直径から半径に変換）
}   t_sphere;

typedef struct s_cylinder
{
	t_vec3	axis; // 中心軸の向き。円柱が伸びている方向
    double	height; //高さ
} t_cylinder;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

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
void	log_elapsed_time(char *prefix_str, double start_time);

#endif // MINIRT_H
