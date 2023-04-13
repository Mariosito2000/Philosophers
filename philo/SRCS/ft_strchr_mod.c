/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_mod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:31:29 by marias-e          #+#    #+#             */
/*   Updated: 2023/03/14 16:28:03 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strchr_mod(const char *s, int c)
{
	int	count;

	count = 0;
	while (s[count])
	{
		if (s[count] == (char)c)
			return (count);
		count++;
	}
	if (s[count] == (char)c)
		return (count);
	return (-1);
}
