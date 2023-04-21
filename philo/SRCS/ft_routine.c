/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:50:59 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/21 11:59:26 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_get_time(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->time = (time.tv_sec * 1000000) + time.tv_usec;
}

int	ft_mute_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->arg->dead_mutex);
	dead = philo->arg->dead;
	pthread_mutex_unlock(&philo->arg->dead_mutex);
	return (dead);
}

void	ft_routine(t_philo *philo)
{
	philo->last_meal = philo->arg->start_time;
	while (TRUE)
	{
		if (philo->activity == EAT && ft_eat(philo))
			break ;
		if (philo->activity == NAP && ft_nap(philo))
			break ;
		if (philo->activity == THINK && ft_think(philo))
			break ;
	}
}
