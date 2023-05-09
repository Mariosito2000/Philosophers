/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:01:15 by marias-e          #+#    #+#             */
/*   Updated: 2023/05/08 18:16:32 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_manage_time(t_arg *arg)
{
	struct timeval	com_time;
	int				dead;

	dead = 0;
	while (dead == 0)
	{
		pthread_mutex_lock(&arg->time_mutex);
		gettimeofday(&com_time, 0);
		arg->time = (com_time.tv_sec * 1000) + (com_time.tv_usec / 1000);
		pthread_mutex_unlock(&arg->time_mutex);
		pthread_mutex_lock(&arg->dead_mutex);
		dead = arg->dead;
		pthread_mutex_unlock(&arg->dead_mutex);
		usleep(800);
	}
}
