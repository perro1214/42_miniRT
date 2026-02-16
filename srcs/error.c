/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 01:17:26 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/16 07:13:37 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	log_error(char *message)
{
	ft_putstr_fd("Error : ", 2);
	ft_putendl_fd(message, 2);
}

char	*get_type(t_object *obj)
{
	static char *type_names[] = {
        [SPHERE] = "SPHERE",
        [CYLINDER] = "CYLINDER",
        [PLANE] = "PLANE",
		[CONE] = "CONE"
    };

	if (!obj || obj->type < 0 || obj->type >= TYPE_MAX)
		return ("UNKNOWN");
	return (type_names[obj->type]);
}
