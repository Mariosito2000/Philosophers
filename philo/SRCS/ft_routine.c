/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:50:59 by marias-e          #+#    #+#             */
/*   Updated: 2023/05/08 17:18:33 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo, int action)
{
	if (action == EAT)
	{
		if (philo->arg->conditions[life_expectancy]
			< philo->arg->conditions[hunger])
			usleep(philo->arg->conditions[life_expectancy] * (800));
		else
			usleep(philo->arg->conditions[hunger] * (800));
	}
	else
	{
		if (philo->arg->conditions[life_expectancy]
			< philo->arg->conditions[nap_time])
			usleep(philo->arg->conditions[life_expectancy] * (800));
		else
			usleep(philo->arg->conditions[nap_time] * (800));
	}
}

void	ft_get_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->time_mutex);
	philo->time = philo->arg->time;
	pthread_mutex_unlock(&philo->arg->time_mutex);
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
		if (ft_eat(philo))
			break ;
		if (ft_nap(philo))
			break ;
		if (ft_think(philo))
			break ;
	}
}
