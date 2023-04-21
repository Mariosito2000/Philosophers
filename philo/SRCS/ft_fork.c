/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:17:31 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/21 13:05:00 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->printer_mutex);
	if (philo->arg->can_print)
	{
		ft_get_time(philo);
		printf("\e[33m%ld %d has taken a fork\n\e[0m", (philo->time
				- philo->arg->start_time) / 1000, philo->id);
	}
	pthread_mutex_unlock(&philo->arg->printer_mutex);
}

int	ft_left_check(t_philo *philo, int *check)
{
	while (*check == 1)
	{
		ft_get_time(philo);
		if (ft_check_death(philo))
			return (1);
		pthread_mutex_lock(philo->left_m);
		if (*philo->left_hand == FREE)
		{
			*philo->left_hand = RIGHT;
			(*check)++;
		}
		pthread_mutex_unlock(philo->left_m);
	}
	return (0);
}

int	ft_right_check(t_philo *philo, int *check)
{
	while (*check == 0)
	{
		ft_get_time(philo);
		if (ft_check_death(philo))
			return (1);
		pthread_mutex_lock(philo->right_m);
		if (*philo->right_hand == FREE)
		{
			*philo->right_hand = LEFT;
			(*check)++;
		}
		pthread_mutex_unlock(philo->right_m);
	}
	return (0);
}
