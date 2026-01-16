/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:27:40 by hayato            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/01/15 01:55:32 by htsutsum         ###   ########.fr       */
=======
/*   Updated: 2026/01/16 11:28:12 by hayato           ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "ray.h"
# include "vec3.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

// debug flag
# ifndef DEBUG
#  define DEBUG 1
# endif

// Window size
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// Keycode
# define KEY_ESCAPE 65307

// Event code
# define EVENT_CLOSE 17

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlx;

typedef enum e_type {
    SPHERE,
    PLANE,
    CYLINDER,
	TYPE_MAX
}					t_type;

typedef struct s_sphere
{
	double radius; // 球の半径 （直径から半径に変換）
}					t_sphere;

typedef struct s_plane
{
	t_vec3 normal; // 法線ベクトル
}					t_plane;

typedef struct s_cylinder
{
	t_vec3 normal; // 法線ベクトル
	double radius; // 半径
	double height; // 高さ
}					t_cylinder;

typedef union u_obj_data
{
	t_sphere		sp;
	t_plane			pl;
	t_cylinder		cy;
}					t_obj_data;

typedef struct s_object
{
	int				type;
	t_vec3			point;
	t_vec3			color;
	t_obj_data		data;
	struct s_object	*next;
}					t_object;

typedef struct s_camera
{
	t_vec3			position;
	t_vec3			direction;
	double			fov;
}					t_camera;

typedef struct s_ambient
{
	double			ratio;
	t_vec3			color;
}					t_ambient;

typedef struct s_light
{
	t_vec3			position;
	double			intensity;
	t_vec3			color;
}					t_light;

typedef struct s_ambient
{
	double ratio;
	t_vec3 color;
}	t_ambient;

typedef struct s_light
{
	t_vec3 point;
	double ratio;
	t_vec3 color;
	struct s_light *next;
}	t_light;

typedef struct s_scene
{
	t_camera	*cam;
	t_ambient	*at;
	t_light		*lts;
	t_object	*objs;
} t_scene;

// mlx_action_close.c
int					key_hook(int keycode, t_mlx *mlx);
int					close_window(t_mlx *mlx);

// render_pixel.c
void				ft_mlx_put_pixel(t_mlx *mlx, int x, int y, int color);
int					vec3_to_color(t_vec3 color);

// error.c
void				log_error(char *message);

// arg_parser.c
int					parse_arguments(int argc, char **argv);

// timer.c
double				current_time_ms(void);
void				log_elapsed_time(char *prefix_str, double start_time);

// hit_sphere.c
double				hit_sphere(t_object *obj, t_ray ray);

// hit_plane.c
double				hit_plane(t_object *obj, t_ray ray);

// screen_norm.c
t_ray				get_ray_fixed(int px, int py);

// rt_loader.c
int					rt_loader(t_object **objs, const char *file_name);

// object_list.c
void				free_objects(t_object *objs);
void				add_object_to_list(t_object **head, t_object *new_obj);

#endif // MINIRT_H
