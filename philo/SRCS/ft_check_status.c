/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:27:44 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/14 13:51:01 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_death(t_philo *philo)
{
	
}

int	ft_eat(t_philo *philo)
{
	while (philo->activity == 0)
	{
		if (ft_mute_death(philo))
			return (1);
		ft_get_time(philo);
		ft_check_death(philo);
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
	ft_dessert(&philo);
	return (0);
}

static void	ft_dessert(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->printer_mutex);
	printf("%d %d is eating\n", philo->last_meal, philo->id);
	pthread_mutex_unlock(&philo->arg->printer_mutex);
	pthread_mutex_lock(philo->right_m);
	pthread_mutex_lock(philo->left_m);
	*philo->right_hand = FREE;
	*philo->left_hand = FREE;
	pthread_mutex_unlock(philo->right_m);
	pthread_mutex_unlock(philo->left_m);
	philo->last_meal = philo->time;
	if (philo->meals_left > 0)
		philo->meals_left--;
}

void	ft_nap(t_philo *philo)
{
	if (philo->last_meal + philo->arg->conditions[hunger] >= philo->time)
	{
		pthread_mutex_lock(&philo->arg->printer_mutex);
		printf("%d %d is sleeping\n", philo->last_meal, philo->id);
		pthread_mutex_unlock(&philo->arg->printer_mutex);
		philo->activity++;
	}
}

void	ft_think(t_philo *philo)
{
	if (philo->last_meal + philo->arg->conditions[hunger]
		+ philo->arg->conditions[nap_time] >= philo->time)
	{
		pthread_mutex_lock(&philo->arg->printer_mutex);
		printf("%d %d is thinking\n", philo->last_meal, philo->id);
		pthread_mutex_unlock(&philo->arg->printer_mutex);
		philo->activity = EAT;
	}
}

/* ft_check_death(philo);
		if (philo->activity == 0 || philo->activity == 1)
			ft_check_fork(philo);
		if (philo->activity == 2)
			ft_eat(philo);
		if (philo->activity == 3)
			ft_nap(philo);
		if (philo->activity == 4)
			ft_think(philo); */