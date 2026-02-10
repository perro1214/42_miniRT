/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 04:36:41 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/10 04:32:12 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// 本当に強制的に正規化していいのか？ ドキュメントとの整合性
// tab、スペース複数、対策するか？ split
// 改行問題 -> get_next_lineはリターンコード含む、リターンコード削除で一応対応済み。
// FOVを0.001 179.99にしているが、度ky面とは0-180の範囲になっているので、調整必要かも?

static int	parse_line(t_scene *scene, char *line);
static void trim_newline(char *line);

// ファイルをリードオンリーで開いて１行づつ読み込み。
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
		if (line[0] != '\n' && line[0] != '\0')
		{
			status = parse_line(scene, line);
			if (status == 0)
				count++;
		}
		free(line);
		if (status == 1)
			break ;
	}
	close(fd);
	if (status == 0 && count == 0)
    {
        log_error("Scene file is empty or contains no valid data");
        return (1);
    }
	return (status);
}

// typeによってデータを読み込み、sceneにデータを追加
static int	parse_line(t_scene *scene, char *line)
{
	char	**rt_data;
	int		status;

	trim_newline(line);
	rt_data = ft_split(line, ' ');
	if (!rt_data|| !rt_data[0])
		return (ft_free_tab(rt_data), 0);
	status = 1;
	if (ft_strcmp(rt_data[0], "A") == 0)
		status = set_ambient(scene, rt_data);
	else if (ft_strcmp(rt_data[0], "C") == 0)
		status = set_camera(scene, rt_data);
	else if (ft_strcmp(rt_data[0], "L") == 0)
		status = set_light(scene, rt_data);
	else if (ft_strcmp(rt_data[0], "sp") == 0 || ft_strcmp(rt_data[0],
			"pl") == 0 || ft_strcmp(rt_data[0], "cy") == 0)
		status = add_new_object(scene, rt_data);
	else
		log_error("Unknown identifier found in .rt file");
	ft_free_tab(rt_data);
	return (status);
}

//少なくともデータがひとつづつあるか?
int	is_valid_scene(t_scene *scene)
{
	if (!scene->cam)
		return (log_error("No camera defined"), 1);
	if (!scene->amb)
		return (log_error("No ambient light defined"), 1);
	if (!scene->ligs)
		return (log_error("No light source defined"), 1);
	if (!scene->objs)
		return (log_error("No objects to render"), 1);
	return (0);
}

// free t_scene
void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free(scene->cam);
	free(scene->amb);
	free_lights(scene->ligs);
	free_objects(scene->objs);
}

// get_next_lineの改行を切り取り
static void trim_newline(char *line)
{
    size_t len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
}
