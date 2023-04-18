/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:27:44 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/18 17:45:59 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death(t_philo *philo)
{
	if (philo->time - philo->last_meal
		>= philo->arg->conditions[life_expectancy] * 1000)
	{
		pthread_mutex_lock(&philo->arg->dead_mutex);
		philo->arg->dead = 1;
		pthread_mutex_unlock(&philo->arg->dead_mutex);
		pthread_mutex_lock(&philo->arg->printer_mutex);
		ft_get_time(philo);
		if (philo->arg->can_print)
			printf("\e[31m%ld %d died\n\e[0m", (philo->time / 1000)
				- (philo->arg->start_time / 1000), philo->id);
		philo->arg->can_print = 0;
		pthread_mutex_unlock(&philo->arg->printer_mutex);
		return (1);
	}
	return (0);
}

static void	ft_dessert(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->printer_mutex);
	ft_get_time(philo);
	if (philo->arg->can_print)
		printf("\e[32m%ld %d is eating\n\e[0m", (philo->time / 1000)
			- (philo->arg->start_time / 1000), philo->id);
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
	philo->last_meal = philo->time;
	philo->meals_left--;
}

int	ft_eat(t_philo *philo)
{
	while (philo->activity < 2)
	{
		ft_get_time(philo);
		if (ft_check_death(philo))
			return (1);
		pthread_mutex_lock(philo->left_m);
		if (*philo->left_hand == FREE)
		{
			ft_take_fork(philo, RIGHT);
			philo->activity++;
		}
		pthread_mutex_unlock(philo->left_m);
		pthread_mutex_lock(philo->right_m);
		if (*philo->right_hand == FREE)
		{
			ft_take_fork(philo, LEFT);
			philo->activity++;
		}
		pthread_mutex_unlock(philo->right_m);
	}
	ft_dessert(philo);
	return (0);
}

void	ft_nap(t_philo *philo)
{
	if (philo->time >= philo->last_meal
		+ (philo->arg->conditions[hunger] * 1000))
	{
		pthread_mutex_lock(&philo->arg->printer_mutex);
		ft_get_time(philo);
		if (philo->arg->can_print)
			printf("\e[35m%ld %d is sleeping\n\e[0m", (philo->time / 1000)
				- (philo->arg->start_time / 1000), philo->id);
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

void	ft_think(t_philo *philo)
{
	if (philo->time >= philo->last_meal
		+ (philo->arg->conditions[hunger] * 1000)
		+ (philo->arg->conditions[nap_time] * 1000))
	{
		pthread_mutex_lock(&philo->arg->printer_mutex);
		ft_get_time(philo);
		if (philo->arg->can_print)
			printf("\e[36m%ld %d is thinking\n\e[0m", (philo->time
					/ 1000) - (philo->arg->start_time / 1000), philo->id);
		pthread_mutex_unlock(&philo->arg->printer_mutex);
		philo->activity = EAT;
	}
}
