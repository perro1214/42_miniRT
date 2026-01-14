/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 04:36:41 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/14 15:19:33 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	set_object(t_object *obj, char *line);
static int	set_sphere(t_object *obj, char **rt_data);
static int	set_plane(t_object *obj, char *rt_data);
static int	set_cylinder(t_object *obj, char *rt_data);

int	rt_loader(const char *file_name)
{
	int			fd;
	char		*line;
	t_object	*obj;

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
		{
			log_error("rt Data error");
			close(fd);
			return (1);
		}
		if (set_object(obj, line))
		{
			free(line);
			close(fd);
			return (1);
		}
	}
	free(line);
	close(fd);
	return (0);
}

static int	set_object(t_object *obj, char *line)
{
	char	**rt_data;
	int		status;

	static const char *const id[] = {"sp", "pl", "cy"};
	if (!line || line[0] == '\0')
		return (1);
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

// sp 0.0,0.0,20.6 12.6 10,0,255
static int	set_sphere(t_object *obj, char **rt_data)
{
	char	**center;
	char	**color;
	int		status;

	if (!rt_data[1] || !rt_data[2] || !rt_data[3])
		return (1);
	center = ft_split(rt_data[1], ',');
	color = ft_split(rt_data[3], ',');

	status = 1;
	if (center && center[0] && center[1] && center[2] && color && color[1]
		&& color[1] && color[2])
	{
		obj->type = SPHERE;
		obj->center = vec3_init(atof(center[0]), atof(center[1]),
				atof(center[2]));
		obj->data.sp.radius = atof(rt_data[2]) / 2.0f;
		obj->color.r = atoi(color[0]);
		obj->color.g = atoi(color[1]);
		obj->color.b = atoi(color[2]);
	}
	if (center)
		ft_free_tab(center);
	if (color)
		ft_free_tab(color);
	return (0);
}

// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
static int	set_plane(t_object *obj, char **rt_data)
{
	(void)line;
	obj->type = PLANE;
	obj->data.pl.normal.x = 1;
	obj->data.pl.normal.y = 2;
	obj->data.pl.normal.z = 3;
	obj->color.r = 0;
	obj->color.g = 0;
	obj->color.b = 0;
	return (0);
}

// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
static int	set_cylinder(t_object *obj, char **rt_data)
{
	(void)line;
	obj->type = CYLINDER;
	obj->data.cy.axis.x = 1;
	obj->data.cy.axis.y = 2;
	obj->data.cy.axis.z = 3;
	obj->color.r = 0;
	obj->color.g = 0;
	obj->color.b = 0;
	return (0);
}
