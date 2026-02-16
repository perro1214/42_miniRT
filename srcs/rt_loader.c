/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 04:36:41 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/17 01:00:02 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	process_line(t_scene *scene, char *line, int *count);
static int	parse_line(t_scene *scene, char *line);
static void	trim_newline(char *line);

int	rt_loader(t_scene *scene, char *file_name)
{
	int		fd;
	char	*line;
	int		status;
	int		count;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (log_error(strerror(errno)), 1);
	status = 0;
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		status = process_line(scene, line, &count);
		if (status == 1)
			break ;
	}
	close(fd);
	if (status == 0 && count == 0)
		return (log_error("Scene file is empty or contains no valid data"), 1);
	return (status);
}

static int	process_line(t_scene *scene, char *line, int *count)
{
	int	status;

	status = 0;
	if (line[0] != '\n' && line[0] != '\0')
	{
		status = parse_line(scene, line);
		if (status == 0)
			(*count)++;
	}
	free(line);
	return (status);
}

static int	parse_line(t_scene *scene, char *line)
{
	char	**rt_data;
	int		status;

	trim_newline(line);
	rt_data = ft_split(line, ' ');
	if (!rt_data || !rt_data[0])
		return (ft_free_tab(rt_data), 0);
	status = 1;
	if (ft_strcmp(rt_data[0], "A") == 0)
		status = set_ambient(scene, rt_data);
	else if (ft_strcmp(rt_data[0], "C") == 0)
		status = set_camera(scene, rt_data);
	else if (ft_strcmp(rt_data[0], "L") == 0)
		status = set_light(scene, rt_data);
	else if (ft_strcmp(rt_data[0], "sp") == 0 || ft_strcmp(rt_data[0],
			"pl") == 0 || ft_strcmp(rt_data[0], "cy") == 0
		|| ft_strcmp(rt_data[0], "co") == 0)
		status = add_new_object(scene, rt_data);
	else
		log_error("Unknown identifier found in .rt file");
	ft_free_tab(rt_data);
	return (status);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free(scene->cam);
	free(scene->amb);
	free_lights(scene->ligs);
	free_objects(scene->objs);
}

static void	trim_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}
