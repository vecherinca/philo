/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:17:22 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/23 22:07:34 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*right_fork; 
	pthread_mutex_t	*left_fork;
	int				last_meal_time;
	int				meal_counter;
	struct s_data			*data;
	pthread_t		thread;

}					t_philo;

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
	pthread_mutex_t write_mutex;  //? is partie monitoring 
	pthread_mutex_t meal_mutex; // partie monitoring
	pthread_mutex_t	check_end_mutex; // partie monitoring

}					t_data;



void				*thread_routine(void *data);
int					ft_atoi(const char *str);

#endif