/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:34:22 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/18 03:22:00 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	head;
	size_t	tail;

	if (s1 == NULL || set == NULL)
		return (ft_strdup(""));
	head = 0;
	while (s1[head] && ft_strchr(set, (int)s1[head]))
		head++;
	tail = ft_strlen(s1) - 1;
	while (tail > head && ft_strrchr(set, (int)s1[tail]))
		tail--;
	if (tail < head)
		return (ft_strdup(""));
	return (ft_substr(s1, head, tail - head + 1));
}
