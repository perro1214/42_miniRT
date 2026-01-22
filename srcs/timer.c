/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:37:55 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/15 00:41:13 by htsutsum         ###   ########.fr       */
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
	long long	total_micros;
	long long	milli_part;
	long long	micro_part;

	total_micros = (long long)((current_time_ms() - start_time) * 1000);
	if (total_micros < 0)
		total_micros = 0;
	milli_part = total_micros / 1000;
	micro_part = total_micros % 1000;
	ft_putstr_fd(prefix_str, 2);
	ft_putnbr_fd(milli_part, 2);
	ft_putstr_fd(".", 2);
	if (micro_part < 100)
		ft_putstr_fd("0", 2);
	if (micro_part < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(micro_part, 2);
	ft_putendl_fd(" ms", 2);
}
