/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:37:55 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/13 14:54:30 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

double	current_time_ms()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec * 1000.0 + (double)tv.tv_usec /1000.0);
}

void	log_elapsed_time(double start_time)
{
	double		diff;
	char		*s_int;
	char		*s_frac;
	long long	f_part;

	diff = current_time_ms() - start_time;
	write(2, "Render Time: ", 13);
	s_int = ft_lltoa((long long)diff);
	if (s_int)
	{
		write(2, s_int, ft_strlen(s_int));
		free(s_int);
	}
	write(2, ".", 1);
	f_part = (long long)round((diff - (long long)diff) * 1000);
	if (f_part < 100) write(2, "0", 1);
	if (f_part < 10)  write(2, "0", 1);
	s_frac = ft_lltoa(f_part);
	if (s_frac)
	{
		write(2, s_frac, ft_strlen(s_frac));
		free(s_frac);
	}
	write(2, " ms\n", 4);

}
