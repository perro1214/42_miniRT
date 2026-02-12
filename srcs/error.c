/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 01:17:26 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/12 12:31:30 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	log_error(char *message)
{
	ft_putstr_fd("Error : ", 2);
	ft_putendl_fd(message, 2);
}

void	log_usage()
{
	ft_putendl_fd("Usage : ./miniRT rtfile.rt",1);
}

void	log_object(t_type type)
{
	if(type == SPHERE)
		ft_putstr_fd("SPHERE", 1);
	else if (type == CYLINDER)
		ft_putstr_fd("CYLINDER", 1);
	else if (type == PLANE)
		ft_putstr_fd("PLANE", 1);
}
