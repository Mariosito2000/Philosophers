/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:50:59 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/14 12:57:02 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(t_philo *philo)
{
	ft_set_init_time(&philo); //reset death time
	while (ft_mute_death(&philo))
	{
		ft_get_time(&philo);
		ft_check_death(&philo);
		if (philo->activity == EAT)
			if (ft_eat(&philo))
				break ;
		if (philo->activity == NAP)
			ft_nap(&philo);
		if (philo->activity == THINK)
			ft_think(&philo);
	}
}
