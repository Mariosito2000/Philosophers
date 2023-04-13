/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hilito.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:33:11 by marias-e          #+#    #+#             */
/*   Updated: 2023/03/27 13:56:16 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_hilito(t_philo *philo)
{
	pthread_mutex_lock(&(philo->arg->fork[1]));
	printf("Life = %d | ID = %d\n",
		philo->arg->conditions[life_expectancy], philo->id);
	//usleep(1000000);
	philo->arg->conditions[life_expectancy]--;
	pthread_mutex_unlock(&(philo->arg->fork[1]));
	return (0);
}
