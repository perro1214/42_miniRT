/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 04:36:41 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/14 21:32:48 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// エラーデータチェック
// 空行があった場合スキップして次へ行く -> 完了
// type別のsplitした個数があっているか A
// 数字、0-9の文字、','と'.'のみのでーたか A
// データの要素が""からでないか A
// 数値にしたときに範囲内かどうか color と normal 数値の範囲が決まっている。 B
// A , B の二つの関数でチェックする
// norm : too many line

static int	set_object(t_object *obj, char *line);
static int	set_sphere(t_object *obj, char **rt_data);
static int	set_plane(t_object *obj, char **rt_data);
static int	set_cylinder(t_object *obj, char **rt_data);

// ファイルをリードオンリーで開いて１行づつ読み込み、タイプ別にobjsに前に追加
int	rt_loader(t_object **objs, const char *file_name)
{
	int			fd;
	char		*line;
	t_object	*new_obj;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		log_error(strerror(errno));
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] != '\n' && line[0] != '\0')
		{
			new_obj = ft_calloc(sizeof(t_object), 1);
			if (new_obj == NULL || set_object(new_obj, line))
			{
				free(line);
				free(new_obj);
				close(fd);
				return (1);
			}
			add_object_to_list(objs, new_obj);
		}
		free(line);
	}
	close(fd);
	return (0);
}

// typeによってobjデータを読み込み、objに変換
static int	set_object(t_object *obj, char *line)
{
	char						**rt_data;
	int							status;
	static const char *const	id[] = {"sp", "pl", "cy"};

	rt_data = ft_split(line, ' ');
	if (!rt_data)
		return (1);
	if (rt_data[0] == NULL)
	{
		ft_free_tab(rt_data);
		return (1);
	}
	status = 1;
	if (ft_strcmp(rt_data[0], id[SPHERE]) == 0)
		status = set_sphere(obj, rt_data);
	else if (ft_strcmp(rt_data[0], id[PLANE]) == 0)
		status = set_plane(obj, rt_data);
	else if (ft_strcmp(rt_data[0], id[CYLINDER]) == 0)
		status = set_cylinder(obj, rt_data);
	ft_free_tab(rt_data);
	return (status);
}

/* sp 0.0,0.0,20.6 12.6 10,0,255
 * type : sp
 * point : 0.0,0.0.20.6
 * diameter : 12.6
 * color [0, 255]: 10,0,255
 * rt_data size : 4
 * 球のデータを読み込む
 */
static int	set_sphere(t_object *obj, char **rt_data)
{
	char	**point;
	char	**color;
	int		status;

	if (!rt_data[1] || !rt_data[2] || !rt_data[3])
		return (1);
	point = ft_split(rt_data[1], ',');
	color = ft_split(rt_data[3], ',');
	status = 1;
	if (point && point[0] && point[1] && point[2] && color && color[0]
		&& color[1] && color[2])
	{
		obj->type = SPHERE;
		obj->point = vec3_init(atof(point[0]), atof(point[1]), atof(point[2]));
		obj->data.sp.radius = atof(rt_data[2]) / 2.0f;
		obj->color = vec3_init(atof(color[0]), atof(color[1]), atof(color[2]));
		status = 0;
	}
	if (point)
		ft_free_tab(point);
	if (color)
		ft_free_tab(color);
	return (status);
}

/* pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
 * type : pl
 * point : 0.0,0.0,-10.0
 * normal [-1, 1]: 0.0,1.0,0.0
 * color [0, 255]: 0,0,255
 * rt_data size : 4
 * 平面のデータを読み込む
 */
static int	set_plane(t_object *obj, char **rt_data)
{
	char	**point;
	char	**color;
	char	**normal;
	int		status;

	if (!rt_data[1] || !rt_data[2] || !rt_data[3])
		return (1);
	point = ft_split(rt_data[1], ',');
	normal = ft_split(rt_data[2], ',');
	color = ft_split(rt_data[3], ',');
	status = 1;
	if (point && point[0] && point[1] && point[2] && color && color[0]
		&& color[1] && color[2])
	{
		obj->type = PLANE;
		obj->point = vec3_init(atof(point[0]), atof(point[1]), atof(point[2]));
		obj->data.pl.normal = vec3_init(atof(normal[0]), atof(normal[1]),
				atof(normal[2]));
		obj->color = vec3_init(atof(color[0]), atof(color[1]), atof(color[2]));
		status = 0;
	}
	if (point)
		ft_free_tab(point);
	if (normal)
		ft_free_tab(normal);
	if (color)
		ft_free_tab(color);
	return (status);
}

/* cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
 * type : cy
 * point : 50.0,0.0.20.6
 * normal [ -1, 1] :0.0,0.0,1.0
 * diameter : 14.2
 * height : 21.42
 * color [0, 255] : 10,0,255
 * rt_data size : 6
 * 円柱のデータをよみこむ
 */
static int	set_cylinder(t_object *obj, char **rt_data)
{
	char	**point;
	char	**color;
	char	**normal;
	int		status;

	if (!rt_data[1] || !rt_data[2] || !rt_data[3])
		return (1);
	point = ft_split(rt_data[1], ',');
	normal = ft_split(rt_data[2], ',');
	color = ft_split(rt_data[5], ',');
	status = 1;
	if (point && point[0] && point[1] && point[2] && color && color[0]
		&& color[1] && color[2])
	{
		obj->type = CYLINDER;
		obj->point = vec3_init(atof(point[0]), atof(point[1]), atof(point[2]));
		obj->data.cy.normal = vec3_init(atof(normal[0]), atof(normal[1]),
				atof(normal[2]));
		obj->data.cy.radius = atof(rt_data[3]) / 2.0f;
		obj->data.cy.height = atof(rt_data[4]);
		obj->color = vec3_init(atof(color[0]), atof(color[1]), atof(color[2]));
		status = 0;
	}
	if (point)
		ft_free_tab(point);
	if (normal)
		ft_free_tab(normal);
	if (color)
		ft_free_tab(color);
	return (status);
}
