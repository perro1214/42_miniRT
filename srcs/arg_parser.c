/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:43:22 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/12 04:35:22 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stddef.h>

#define ERR_INVALID_NUM "Invalid number of arguments"
#define ERR_INVALID_EXT "File must have .rt extention"

static void	usage(char *prog_name);
static int	is_rt_file(char *file);

int	parse_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		log_error(ERR_INVALID_NUM);
		usage(argv[0]);
		return (1);
	}
	if (!is_rt_file(argv[1]))
	{
		log_error(ERR_INVALID_EXT);
		return (1);
	}
	return (0);
}

static int	is_rt_file(char *file)
{
	size_t	len;

	if (!file)
		return (0);
	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if (file[len - 4] == '/')
		return (0);
	if (ft_strncmp(file + len - 3, ".rt", 3) == 0)
		return (1);
	return (0);
}

static void	usage(char *prog_name)
{
	ft_putstr_fd("Usage : ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(" [filename.rt]", 2);
}
