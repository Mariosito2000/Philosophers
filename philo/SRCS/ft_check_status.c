/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:27:44 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/21 13:05:11 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death(t_philo *philo)
{
	if (ft_mute_death(philo))
		return (1);
	ft_get_time(philo);
	if (philo->time - philo->last_meal
		>= philo->arg->conditions[life_expectancy] * 1000)
	{
		pthread_mutex_lock(&philo->arg->dead_mutex);
		philo->arg->dead = 1;
		pthread_mutex_unlock(&philo->arg->dead_mutex);
		pthread_mutex_lock(&philo->arg->printer_mutex);
		if (philo->arg->can_print)
		{
			ft_get_time(philo);
			printf("\e[31m%ld %d died\n\e[0m", (philo->time
					- philo->arg->start_time) / 1000, philo->id);
		}
		philo->arg->can_print = 0;
		pthread_mutex_unlock(&philo->arg->printer_mutex);
		return (1);
	}
	return (0);
}

static void	ft_dessert(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->printer_mutex);
	if (philo->arg->can_print)
	{
		ft_get_time(philo);
		printf("\e[32m%ld %d is eating\n\e[0m", (philo->time
				- philo->arg->start_time) / 1000, philo->id);
		philo->last_meal = philo->time;
	}
	philo->meals_left--;
	if (philo->meals_left == 0)
		philo->arg->satisfaction--;
	if (philo->arg->satisfaction == 0)
	{
		philo->arg->can_print = 0;
		pthread_mutex_lock(&philo->arg->dead_mutex);
		philo->arg->dead = 1;
		pthread_mutex_unlock(&philo->arg->dead_mutex);
	}
	pthread_mutex_unlock(&philo->arg->printer_mutex);
	philo->activity++;
}

int	ft_eat(t_philo *philo)
{
	int	check;

	check = 0;
	if (ft_right_check(philo, &check))
		return (1);
	ft_take_fork(philo);
	if (ft_left_check(philo, &check))
		return (1);
	ft_take_fork(philo);
	ft_dessert(philo);
	return (0);
}

int	ft_nap(t_philo *philo)
{
	while (philo->activity == NAP)
	{
		if (ft_check_death(philo))
			return (1);
		if (philo->time >= philo->last_meal
			+ (philo->arg->conditions[hunger] * 1000))
		{
			pthread_mutex_lock(&philo->arg->printer_mutex);
			if (philo->arg->can_print)
			{
				ft_get_time(philo);
				printf("\e[35m%ld %d is sleeping\n\e[0m", (philo->time
						- philo->arg->start_time) / 1000, philo->id);
			}
			pthread_mutex_unlock(&philo->arg->printer_mutex);
			pthread_mutex_lock(philo->right_m);
			*philo->right_hand = FREE;
			pthread_mutex_unlock(philo->right_m);
			pthread_mutex_lock(philo->left_m);
			*philo->left_hand = FREE;
			pthread_mutex_unlock(philo->left_m);
			philo->activity = THINK;
		}
	}
	return (0);
}

int	ft_think(t_philo *philo)
{
	while (philo->activity == THINK)
	{
		if (ft_check_death(philo))
			return (1);
		if (philo->time >= philo->last_meal
			+ (philo->arg->conditions[hunger] * 1000)
			+ (philo->arg->conditions[nap_time] * 1000))
		{
			pthread_mutex_lock(&philo->arg->printer_mutex);
			if (philo->arg->can_print)
			{
				ft_get_time(philo);
				printf("\e[36m%ld %d is thinking\n\e[0m", (philo->time
						- philo->arg->start_time) / 1000, philo->id);
			}
			pthread_mutex_unlock(&philo->arg->printer_mutex);
			philo->activity = EAT;
		}
	}
	return (0);
}
