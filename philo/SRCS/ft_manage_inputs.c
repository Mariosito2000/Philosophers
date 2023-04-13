/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_inputs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:14:04 by marias-e          #+#    #+#             */
/*   Updated: 2023/03/25 14:06:04 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_chr(char *str)
{
	int	i;

	if ((str[0] == '-' && str[1] == '0'))
		return (1);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_strchr_mod("0123456789", str[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_check_limits(int n, char	*str)
{
	if (((n < 0 || ft_strlen(str) > 10) && str[0] != '-')
		|| (ft_strlen(str) >= 10 && str[0] > '2'))
		return (1);
	if (((n == 0 || ft_strlen(str) > 11) && str[0] == '-')
		|| (ft_strlen(str) >= 11 && str[1] > '2'))
		return (1);
	return (0);
}

static int	ft_add_number(char *arg, int *conditions)
{
	int	error;

	error = ft_check_chr(arg);
	if (error)
		return (error);
	*conditions = ft_atoi(arg);
	if (ft_check_limits(*conditions, arg))
		return (22);
	return (0);
}

int	ft_manage_inputs(int argc, char **argv, int	*conditions)
{
	int		i;
	int		error;

	i = 1;
	while (i < argc)
	{
		error = ft_add_number(argv[i], &conditions[i - 1]);
		if (error || conditions[i - 1] < 0)
			return (1);
		i++;
	}
	if (conditions[n_philos] == 0
		|| (argc == 6 && conditions[eating_times] == 0))
		return (1);
	if (argc == 5)
		conditions[eating_times] = -1;
	return (0);
}
