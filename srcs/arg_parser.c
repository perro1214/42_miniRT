/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:43:22 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/12 02:17:32 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define ERR_INVALID_NUM "Invalid number of arguments"

static void	_usage(char *prog_name);

int	parse_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		log_error(ERR_INVALID_NUM);
		_usage(argv[0]);
		return (1);
	}
	return (0);
}

static void	_usage(char *prog_name)
{
	ft_putstr_fd("Usage : ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putendl_fd(" [filename.rt]\n", 2);
}
