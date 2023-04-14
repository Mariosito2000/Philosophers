/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:03:04 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/14 12:53:01 by marias-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <pthread.h>
# include <sys/time.h>

# define FALSE	0
# define TRUE	1

# define FREE	0
# define RIGHT	1
# define LEFT	2

# define EAT	0
# define NAP	1
# define THINK	2

enum e_conditions
{
	n_philos = 0,
	life_expectancy = 1,
	hunger = 2,
	nap_time = 3,
	eating_times = 4
};

typedef struct s_arg
{
	int				conditions[5];
	struct timeval	time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	printer_mutex;
	pthread_mutex_t	dead_mutex;
	int				dead;
	int				*forkstate; // free, left, right
}	t_arg;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				time;
	int				last_meal;	// last meal mark al empezar la función
	pthread_mutex_t	*right_m;
	pthread_mutex_t	*left_m;
	int				*left_hand;
	int				*right_hand; // puntero a la mesa
	int				meals_left;	// number of meals
	int				dead;		// 0 alive, 1 dead
	int				activity;	// 0 pensar, 1-2 coger, 3 comer, 4 dormir
	t_arg			*arg;
}	t_philo;

void		*ft_malloc(int size);
size_t		ft_strlen(const char *str);
int			ft_atoi(const char *str);
int			ft_strchr_mod(const char *s, int c);

int			ft_manage_inputs(int argc, char **argv, int	*conditions);

int			ft_create_academy(t_arg *arg, t_philo **philos);

void		*ft_hilito(t_philo *philo);

#endif