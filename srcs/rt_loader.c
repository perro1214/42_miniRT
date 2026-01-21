/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 04:36:41 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/22 00:38:21 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// エラーデータチェック
// 空行があった場合スキップして次へ行く -> 完了
// type別のsplitした個数があっているか -> ft_count_tab完了
// 数字、0-9の文字、','と'.'-のみのデータか > is_valid_double_str完了
// データの要素が""からでないか、splitで分けた時、数をチェック> 完了
// 数値にしたときに範囲内かどうか color と normal 数値の範囲が決まっている。 ->完了
// normal どうちぇっくするか -> is_normalized正規化できるかチェック ->完了
// norm : too many line -> 完了
// camera,ambient,light,objectが少なくとも一つないとエラーを表示 -> is_valid_scene関数
// get_next_lineの最後の改行を切り取りする -> trim_newline 暫定
// tab、スペース複数、対策するか？

static int	parse_line(t_scene *scene, char *line);
static void trim_newline(char *line);

// ファイルをリードオンリーで開いて１行づつ読み込み。
int	rt_loader(t_scene *scene, char *file_name)
{
	int		fd;
	char	*line;
	int		status;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (log_error(strerror(errno)), 1);
	status = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] != '\n' && line[0] != '\0')
			status = parse_line(scene, line);
		free(line);
		if (status == 1)
			break ;
	}
	close(fd);
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
