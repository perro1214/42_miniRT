/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:27:40 by hayato            #+#    #+#             */
/*   Updated: 2026/02/11 13:38:45 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _USE_MATH_DEFINES
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "ray.h"
# include "vec3.h"
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

// debug flag
# ifndef DEBUG
#  define DEBUG 1
# endif

// EPSILON
#ifndef EPSILON
# define EPSILON 1e-4
#endif

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

typedef enum e_type
{
    SPHERE,
    PLANE,
    CYLINDER,
	CIRCLE,
	TYPE_MAX
}	t_type;

typedef struct s_transform
{
	t_vec3 pos;  // 移動後の位置
	t_vec3 normal; // 法線
	t_vec3 angle;// 現在の回転各（ラジアン）
}	t_transform;

typedef struct s_sphere
{
	double radius; // 球の半径 （直径から半径に変換）
}	t_sphere;

typedef struct s_plane
{
	t_vec3 normal; // 法線ベクトル
}					t_plane;

typedef struct s_cylinder
{
	t_vec3 normal; // 法線ベクトル
	double radius; // 半径
	double height; // 高さ
} t_cylinder;

typedef struct s_circle
{
	t_vec3 normal; //法線ベクトル
	double radius;
}	t_circle;

typedef union u_obj_data
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
	t_circle	ci;
} t_obj_data;

typedef struct s_object
{
	int				type;
	t_vec3			pos;
	t_vec3			color;
	t_obj_data		data;
	t_transform		curr;
	struct s_object	*next;
}	t_object;

typedef struct s_camera
{
	t_vec3			pos; // 初期値
	t_vec3			dir;
	double			fov;
	t_transform		curr; // 動かす値
	t_vec3			right; // 計算済みデータ、レイ計算高速化
	t_vec3			up;
}	t_camera;

typedef struct s_ambient
{
	double			ratio;
	t_vec3			color;
}	t_ambient;

typedef struct s_light
{
	t_vec3			pos;
	double			intensity;
	t_vec3			color;
	t_transform		curr;
	struct s_light	*next;
}	t_light;

// 前から3文字で統一、sで複数
typedef struct s_scene
{
	t_mlx		*mlx;
	t_camera	*cam;
	t_ambient	*amb;
	t_light		*ligs;
	t_object	*objs;
	t_object	*selected_obj;
} 	t_scene;

// mlx_action_close.c
int		key_hook(int keycode, t_scene *scene);
int		mouse_hook(int button, int x, int y, t_scene *scene);
int		expose_hook(t_scene *scene);
int		close_window(t_scene *scene);

// render_pixel.c
void	ft_mlx_put_pixel(t_mlx *mlx, int x, int y, int color);

// error.c
void	log_error(char *message);

// arg_parser.c
int		parse_arguments(int argc, char **argv);

// timer.c
double	current_time_ms(void);
void	log_elapsed_time(char *prefix_str, double start_time);

// hit_sphere.c
double	hit_sphere(t_object *obj, t_ray ray);

// hit_plane.c
double	hit_plane(t_object *obj, t_ray ray);

// hit_cylinder
double hit_cylinder(t_object *obj, t_ray ray);

// hit_circle
double	hit_circle(t_object *obj, t_ray ray);

// hit_util
int		solve_quadratic(double a, double b, double c, double *t1, double *t2);
double	hit_disk(t_ray ray, t_vec3 center, t_vec3 normal, double radius);

// screen_norm.c
t_ray	get_ray_fixed(int px, int py);
t_ray	get_ray(int px, int py, t_camera *cam);

// rt_loader.c
int		rt_loader(t_scene *scene, char *file_name);
int		is_valid_scene(t_scene *scene);
void	free_scene(t_scene *scene);

// set_object.c
int		set_sphere(t_object *obj, char **rt_data);
int		set_plane(t_object *obj, char **rt_data);
int		set_cylinder(t_object *obj, char **rt_data);

// set_scene.c
int		set_ambient(t_scene *scene, char **rt_data);
int		set_camera(t_scene *scene, char **rt_data);
int		set_light(t_scene *scene, char **rt_data);
void	free_lights(t_light *lights);

// object_util.c
int		add_new_object(t_scene *scene, char **rt_data);
void	add_object_to_list(t_object **head, t_object *new_obj);
void	free_objects(t_object *objs);

// rt_parse_util.c
t_vec3	str_to_vec3(char *str, int *status);
double	get_double(char *str, int *status);

//color_util.c
t_vec3	color_to_unit(t_vec3 color);
int		vec3_to_color(t_vec3 color);
t_vec3	denormalize_color(t_vec3 color);
t_vec3	clamp_color(t_vec3 color);

//rt_validator.c
int		is_in_range(double value, double min, double max);
int 	is_valid_normal(t_vec3 normal);
int 	is_valid_normal_vec(t_vec3 normal);
int		is_normalized(t_vec3 vec);
int 	is_valid_color(t_vec3 color);

// camera_util.c
void	update_camera(t_camera *cam);

// render_scene.c
void		render_scene(t_scene *scene);
t_object	*find_closest_obj(t_scene *scene, t_ray ray, double *out_t);

#endif // MINIRT_H
