/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:54:48 by mklimina          #+#    #+#             */
/*   Updated: 2023/11/03 19:15:44 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_general_info(char **argv, t_data *data, int argc)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->nb_must_eat = ft_atoi(argv[5]);
		if (data->nb_must_eat <= 0)
			return (free(data), NULL);
	}
	else
		data->nb_must_eat = -1;
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (free(data), NULL);
	data->start_time = actual_time();
	data->all_ate = 0;
	data->phi_died = 0;
	data = init_mallocs(data);
	if (!data)
		return (NULL);
	return (data);
}

t_data	*init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (free(data), NULL);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (pthread_mutex_destroy(&data->write_mutex), free(data), NULL);
	if (pthread_mutex_init(&data->check_end_mutex, NULL))
		return (pthread_mutex_destroy(&data->write_mutex),
			pthread_mutex_destroy(&data->meal_mutex),
			free(data),
			NULL);
	return (data);
}

t_data	*mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data = init_mutex(data);
	if (!data)
		return (NULL);
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&data->forks[i]);
			}
			pthread_mutex_destroy(&data->write_mutex);
			pthread_mutex_destroy(&data->meal_mutex);
			pthread_mutex_destroy(&data->check_end_mutex);
			free(data->philo);
			free(data->forks);
			free(data);
		}
		i++;
	}
	return (data);
}

t_data	*init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal_time = 0;
		data->philo[i].meal_counter = 0;
		data->philo[i].data = data;
		if (i % 2 != 0)
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

t_data	*init_data(char **argv, t_data *data, int argc)
{
	data = init_general_info(argv, data, argc);
	if (!data)
		return (NULL);
	data = mutex_init(data);
	if (!data)
		return (NULL);
	data = init_philo(data);
	return (data);
}
