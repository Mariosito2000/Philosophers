/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:17:31 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/14 13:23:00 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo, int fork)
{
	if (fork == LEFT)
		*philo->right_hand = LEFT;
	else
		*philo->left_hand = RIGHT;
	pthread_mutex_lock(&philo->arg->printer_mutex);
	printf("%d %d has taken a fork\n", philo->last_meal, philo->id);
	pthread_mutex_unlock(&philo->arg->printer_mutex);
}
