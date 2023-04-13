/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:50:59 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/13 10:33:27 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(t_philo *philo)
{
	ft_set_init_time(&philo); //reset death time
	while (ft_mute_death(&philo))
	{
		if (philo->activity == 0 || philo->activity == 1)
			ft_check_fork(&philo);
		if (philo->activity == 2)
			ft_eat(&philo);
		if (philo->activity == 3)
			ft_nap(&philo);
		if (philo->activity == 4)
			ft_think(&philo);
		ft_get_time(&philo);
		ft_check_death(&philo);
	}
}
