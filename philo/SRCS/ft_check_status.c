/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:27:44 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/17 13:59:33 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death(t_philo *philo)
{
	if (philo->time - philo->last_meal
		>= philo->arg->conditions[life_expectancy] * 1000)
	{
		pthread_mutex_lock(&philo->arg->printer_mutex);
		pthread_mutex_lock(&philo->arg->dead_mutex);
		if (!philo->arg->dead)
			printf("%ld %d died\n", philo->time / 1000 - philo->start_time
				/ 1000, philo->id);
		philo->arg->dead = 1;
		pthread_mutex_unlock(&philo->arg->printer_mutex);
		pthread_mutex_unlock(&philo->arg->dead_mutex);
		return (1);
	}
	return (0);
}

static void	ft_dessert(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->printer_mutex);
	printf("%ld %d is eating\n", philo->time / 1000 - philo->start_time
		/ 1000, philo->id);
	pthread_mutex_unlock(&philo->arg->printer_mutex);
	philo->last_meal = philo->time;
	if (philo->meals_left > 0)
		philo->meals_left--;
}

int	ft_eat(t_philo *philo)
{
	while (philo->activity == 0)
	{	
		ft_get_time(philo);
		if (ft_check_death(philo))
			return (1);
		pthread_mutex_lock(philo->right_m);
		pthread_mutex_lock(philo->left_m);
		if (*philo->right_hand == FREE)
			ft_take_fork(philo, LEFT);
		if (*philo->left_hand == FREE)
			ft_take_fork(philo, RIGHT);
		if (*philo->right_hand == LEFT && *philo->left_hand == RIGHT)
			philo->activity++;
		pthread_mutex_unlock(philo->right_m);
		pthread_mutex_unlock(philo->left_m);
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
		printf("%ld %d is sleeping\n", philo->time / 1000 - philo->start_time
			/ 1000, philo->id);
		pthread_mutex_unlock(&philo->arg->printer_mutex);
		pthread_mutex_lock(philo->right_m);
		pthread_mutex_lock(philo->left_m);
		*philo->right_hand = FREE;
		*philo->left_hand = FREE;
		pthread_mutex_unlock(philo->right_m);
		pthread_mutex_unlock(philo->left_m);
		philo->activity++;
	}
}

void	ft_think(t_philo *philo)
{
	if (philo->time >= philo->last_meal
		+ (philo->arg->conditions[hunger] * 1000)
		+ (philo->arg->conditions[nap_time] * 1000))
	{
		pthread_mutex_lock(&philo->arg->printer_mutex);
		printf("%ld %d is thinking\n", philo->time
			/ 1000 - philo->start_time / 1000, philo->id);
		pthread_mutex_unlock(&philo->arg->printer_mutex);
		philo->activity = EAT;
	}
}
