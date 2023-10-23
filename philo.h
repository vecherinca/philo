/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:17:22 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/23 20:29:47 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	long int		start_time;
	int				number_of_philosophers;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				nb_must_eat;
	int				all_ate;
	int				phi_died;
	t_philo			**philo;
	pthread_mutex_t write_mutex;  
	pthread_mutex_t meal_mutex; 
	pthread_mutex_t	check_end_mutex;

}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				last_meal_time;
	int				meal_counter;
	pthread_t		thread;
	t_data			*data;

}					t_philo;

void				*thread_routine(void *data);

#endif