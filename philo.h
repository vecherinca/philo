/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:17:22 by mklimina          #+#    #+#             */
/*   Updated: 2023/11/01 15:34:09 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include "printf/ft_printf.h"

#define TAKE_FORK "has taken a fork"
#define EATING "is eating"
#define SLEEPING "is sleeping"
#define THINKING "is thinking"
#define DEAD "is dead"

struct s_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*fork_one; 
	pthread_mutex_t	*fork_two;
	long int				last_meal_time;
	int				meal_counter;
	struct s_data			*data;
	pthread_t		thread;

}					t_philo;

typedef struct s_data
{
	long int		start_time;
	int				number_of_philosophers;
	long int				time_to_eat;
	long int				time_to_die;
	int				time_to_sleep;
	int				nb_must_eat;
	int				all_ate;
	int				phi_died;
	t_philo			*philo;
	pthread_mutex_t *forks;
	pthread_mutex_t write_mutex;  //? is partie monitoring 
	pthread_mutex_t meal_mutex; // partie monitoring
	pthread_mutex_t	check_end_mutex; // partie monitoring

}					t_data;



int					ft_atoi(const char *str);


#endif