/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:27:44 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/13 12:10:07 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_death(t_philo *philo)
{
	
}

void	ft_check_fork(t_philo *philo)
{
	
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_m);
	pthread_mutex_lock(philo->left_m);
	if (*(philo->left_hand) == RIGHT && *(philo->right_hand) == LEFT)
	{
		philo->last_meal = philo->time;
		if (philo->meals_left > 0)
			philo->meals_left--;
		pthread_mutex_lock(philo->arg->printer);
		printf("%d %d is eating\n", philo->last_meal, philo->id);
		pthread_mutex_unlock(philo->arg->printer);
		philo->activity++;
	}
	pthread_mutex_unlock(philo->right_m);
	pthread_mutex_unlock(philo->left_m);
}

void	ft_nap(t_philo *philo)
{
	if (philo->last_meal + philo->arg->conditions[hunger] >= philo->time)
	{
		
	}
}

void	ft_think(t_philo *philo)
{
	
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