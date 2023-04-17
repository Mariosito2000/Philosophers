/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:36:04 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/17 14:05:13 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg		arg;
	t_philo		*philos;

	philos = NULL;
	if (argc < 5 || argc > 6)
		return (1);
	if (ft_manage_inputs(argc, argv, arg.conditions))
		return (1);
	if (ft_create_academy(&arg, &philos))
		return (1);
	return (0);
}

//INICIALIZAR ESTRUCTURAS A 0 PARA CHECKEAR SI HACER FREE
//LIBERAR TODO ANTES DE CADA RETURN