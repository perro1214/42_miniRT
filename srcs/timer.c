/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:37:55 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/13 19:06:26 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include <sys/time.h>

double	current_time_ms()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec * 1000.0 + (double)tv.tv_usec /1000.0);
}

void	log_elapsed_time(char *prefix_str, double start_time)
{
	double		diff;
	char		*int_str;
	char		*frac_str;
	long long	f_part;

	diff = current_time_ms() - start_time;
	ft_putstr_fd(prefix_str, 2);
	int_str = ft_lltoa((long long)diff);
	if (int_str)
	{
		ft_putstr_fd(int_str, 2);
		free(int_str);
	}
	ft_putstr_fd(".", 2);
	f_part = (long long)round((diff - (long long)diff) * 1000);
	if (f_part < 100)
		ft_putstr_fd("0", 2);
	if (f_part < 10)
		ft_putstr_fd("0", 2);
	frac_str = ft_lltoa(f_part);
	if (frac_str)
	{
		ft_putstr_fd(frac_str, 2);
		free(frac_str);
	}
	ft_putendl_fd(" ms", 2);
}
