/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:57:26 by mklimina          #+#    #+#             */
/*   Updated: 2023/11/03 18:46:51 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (!(philo->id % 2))
		ft_usleep(philo, philo->data->time_to_eat / 2);
	while (1)
	{
		if (eat(philo) == 0)
			return ((void *)0);
		if (sleep_philo(philo) == 0)
			return ((void *)0);
		if (to_think(philo) == 0)
			return ((void *)0);
		if (philo->data->number_of_philosophers % 2)
			ft_usleep(philo, philo->data->time_to_die
				- (philo->data->time_to_eat + philo->data->time_to_sleep));
	}
	return ((void *)1);
}

void	free_everything(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->check_end_mutex);
	free(data->forks);
	free(data->philo);
	free(data);
}

void	threading(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&(data->philo[i].thread), NULL, &routine,
				&data->philo[i]))
		{
			printf("ERROR THREAD CREATING\n");
			free_everything(data);
			exit(1);
		}
		i++;
	}
}

void	joining(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join((data->philo[i].thread), NULL))
		{
			printf("ERROR THREAD JOINING\n");
			free_everything(data);
			exit(1);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (0);
	data = malloc(sizeof(t_data));
	data = init_data(argv, data, argc);
	if (!data)
	{
		printf("Parsing error: Check the arguments, something is wrong ;)");
		return (0);
	}
	threading(data);
	monitoring(data->philo);
	joining(data);
	free_everything(data);
}
