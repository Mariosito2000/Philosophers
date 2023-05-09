/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:17:31 by marias-e          #+#    #+#             */
/*   Updated: 2023/05/08 18:26:21 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->printer_mutex);
	if (philo->arg->can_print)
	{
		printf("\e[33m%ld %d has taken a fork\n\e[0m", philo->time
			- philo->arg->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->arg->printer_mutex);
}

int	ft_left_check(t_philo *philo, int *check)
{
	int	checky;

	checky = *check;
	while (*check == checky)
	{
		if (ft_check_death(philo))
			return (1);
		pthread_mutex_lock(philo->left_m);
		if (*philo->left_hand == FREE)
		{
			*philo->left_hand = RIGHT;
			(*check)++;
		}
		pthread_mutex_unlock(philo->left_m);
		if (*check == checky)
			usleep(philo->arg->conditions[hunger] >> 1);
	}
	pthread_mutex_lock(&philo->arg->printer_mutex);
	if (philo->arg->can_print)
	{
		printf("\e[33m%ld %d has taken a fork\n\e[0m", philo->time
			- philo->arg->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->arg->printer_mutex);
	return (0);
}

int	ft_right_check(t_philo *philo, int *check)
{
	int	checky;

	checky = *check;
	while (*check == checky)
	{
		if (ft_check_death(philo))
			return (1);
		pthread_mutex_lock(philo->right_m);
		if (*philo->right_hand == FREE)
		{
			*philo->right_hand = LEFT;
			(*check)++;
		}
		pthread_mutex_unlock(philo->right_m);
		if (*check == checky)
			usleep(philo->arg->conditions[hunger] >> 1);
	}
	pthread_mutex_lock(&philo->arg->printer_mutex);
	if (philo->arg->can_print)
	{
		printf("\e[33m%ld %d has taken a fork\n\e[0m", philo->time
			- philo->arg->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->arg->printer_mutex);
	return (0);
}
