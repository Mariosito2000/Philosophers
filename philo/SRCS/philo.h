/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marias-e <marias-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:03:04 by marias-e          #+#    #+#             */
/*   Updated: 2023/04/21 12:04:19 by marias-e         ###   ########.fr       */
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
	pthread_mutex_t	*fork;
	pthread_mutex_t	printer_mutex;
	pthread_mutex_t	dead_mutex;
	int				dead;
	int				can_print;
	int				satisfaction;
	int				*forkstate;
	long int		start_time;
}	t_arg;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long int		time;
	long int		last_meal;
	pthread_mutex_t	*right_m;
	pthread_mutex_t	*left_m;
	int				*left_hand;
	int				*right_hand;
	int				meals_left;
	int				activity;
	t_arg			*arg;
}	t_philo;

size_t		ft_strlen(const char *str);
int			ft_atoi(const char *str);
int			ft_strchr_mod(const char *s, int c);

int			ft_manage_inputs(int argc, char **argv, int	*conditions);

int			ft_create_academy(t_arg *arg, t_philo **philos);

void		ft_routine(t_philo *philo);
void		ft_get_time(t_philo *philo);
int			ft_mute_death(t_philo *philo);
int			ft_check_death(t_philo *philo);
int			ft_eat(t_philo *philo);
int			ft_left_check(t_philo *philo, int *check);
int			ft_right_check(t_philo *philo, int *check);
void		ft_take_fork(t_philo *philo);
int			ft_nap(t_philo *philo);
int			ft_think(t_philo *philo);

void		ft_destroy_mutex(t_arg *arg);
void		ft_free(t_philo **philos, t_arg *arg);

#endif