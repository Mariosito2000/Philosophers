/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:36:04 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/19 13:38:21 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg		arg;
	t_philo		*philos;
	int			out;

	out = 0;
	philos = NULL;
	arg.fork = NULL;
	arg.forkstate = NULL;
	if (argc < 5 || argc > 6)
		return (1);
	if (ft_manage_inputs(argc, argv, arg.conditions))
		return (1);
	if (ft_create_academy(&arg, &philos))
		out = 1;
	ft_destroy_mutex(&arg);
	ft_free(&philos, &arg);
	return (out);
}
