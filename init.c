/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:54:48 by mklimina          #+#    #+#             */
/*   Updated: 2023/11/02 20:55:21 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(char **argv, t_data *data, int argc)
{
	int	i;

	i = 0;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->nb_must_eat = ft_atoi(argv[5]);
		if (data -> nb_must_eat <= 0)
			return(free(data), NULL);
	}
	else
		data->nb_must_eat = -1;
		
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0 \
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (free(data),NULL);
	data->start_time = actual_time();
	data->all_ate = 0;
	data->phi_died = 0;
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->check_end_mutex, NULL);
	// init array of the mutexes forks
	/*
	PHILO init 
	*/
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal_time = 0;
		data->philo[i].meal_counter = 0;
		data->philo[i].data = data;
		if (data->philo[i].id % 2)
		{
			data->philo[i].fork_one = &data->forks[(i + 1)
				% data->number_of_philosophers];
			data->philo[i].fork_two = &data->forks[i];
		}
		else
		{
			data->philo[i].fork_one = &data->forks[i];
			data->philo[i].fork_two = &data->forks[(i + 1)
				% data->number_of_philosophers];
		}
		i++;
	}
	return (data);
}