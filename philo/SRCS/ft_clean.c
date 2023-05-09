/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:50:58 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/24 17:35:26 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_arg *arg)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&arg->time_mutex);
	pthread_mutex_destroy(&arg->dead_mutex);
	pthread_mutex_destroy(&arg->printer_mutex);
	while (i < arg->conditions[n_philos])
	{
		pthread_mutex_destroy(&(arg->fork[i]));
		i++;
	}
}

void	ft_free(t_philo **philos, t_arg *arg)
{
	if (philos && *philos)
		free(*philos);
	if (arg->fork)
		free(arg->fork);
	if (arg->forkstate)
		free(arg->forkstate);
}
