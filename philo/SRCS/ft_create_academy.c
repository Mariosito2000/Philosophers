/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_academy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:45:20 by marias-e          #+#    #+#             */
/*   Updated: 2023/05/08 18:21:43 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_initialize_philo(t_philo *philos, int id, t_arg *arg)
{
	philos->id = id;
	philos->activity = 0;
	philos->meals_left = arg->conditions[eating_times];
	philos->arg = arg;
	philos->left_hand = &(arg->forkstate[id - 1]);
	if (id == arg->conditions[n_philos])
		philos->right_hand = &(arg->forkstate[0]);
	else
		philos->right_hand = &(arg->forkstate[id]);
	philos->left_m = &(arg->fork[id - 1]);
	if (id == arg->conditions[n_philos])
		philos->right_m = &(arg->fork[0]);
	else
		philos->right_m = &(arg->fork[id]);
}

int	ft_init_mutex(t_arg *arg, t_philo **philos)
{
	int	i;

	i = 0;
	arg->time = 0;
	arg->satisfaction = arg->conditions[n_philos];
	arg->can_print = 1;
	arg->dead = 0;
	if (pthread_mutex_init(&arg->time_mutex, 0))
		return (1);
	if (pthread_mutex_init(&arg->dead_mutex, 0))
		return (1);
	if (pthread_mutex_init(&arg->printer_mutex, 0))
		return (1);
	while (i < arg->conditions[n_philos])
	{
		if (pthread_mutex_init(&arg->fork[i], 0))
			return (1);
		ft_initialize_philo(&((*philos)[i]), i + 1, arg);
		arg->forkstate[i] = 0;
		i++;
	}
	return (0);
}

static int	ft_create_threads(t_arg *arg, t_philo **philos)
{
	int	i;

	i = 0;
	if (pthread_create((&arg->time_manager), NULL, (void *)&ft_manage_time,
			&(*arg)))
		return (1);
	usleep (200);
	while (i < arg->conditions[n_philos])
	{
		if (pthread_create(&((*philos)[i].thread), NULL, (void *)&ft_routine,
			&((*philos)[i])))
			return (1);
		i += 2;
	}
	usleep (400);
	i = 1;
	while (i < arg->conditions[n_philos])
	{
		if (pthread_create(&((*philos)[i].thread), NULL, (void *)&ft_routine,
			&((*philos)[i])))
			return (1);
		i += 2;
	}
	return (0);
}

int	ft_join(t_arg *arg, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < arg->conditions[n_philos])
	{
		if (pthread_join((*philos)[i].thread, 0))
			return (1);
		i++;
	}
	if (pthread_join(arg->time_manager, 0))
		return (1);
	return (0);
}

int	ft_create_academy(t_arg *arg, t_philo **philos)
{
	struct timeval	time;

	arg->forkstate = malloc(sizeof(int) * arg->conditions[n_philos]);
	if (!arg->forkstate)
		return (12);
	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->conditions[n_philos]);
	if (!arg->fork)
		return (12);
	*philos = malloc(sizeof(t_philo) * arg->conditions[n_philos]);
	if (!*philos)
		return (12);
	if (ft_init_mutex(arg, philos))
		return (1);
	gettimeofday(&time, NULL);
	arg->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (ft_create_threads(arg, philos))
		return (1);
	if (ft_join(arg, philos))
		return (1);
	return (0);
}
