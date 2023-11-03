/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:58:15 by mklimina          #+#    #+#             */
/*   Updated: 2023/11/03 18:47:22 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_meals(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->nb_must_eat != -1)
	{
		while (i < philo->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->data->meal_mutex);
			if (philo[i].meal_counter < philo->data->nb_must_eat)
			{
				pthread_mutex_unlock(&philo->data->meal_mutex);
				break ;
			}
			pthread_mutex_unlock(&philo->data->meal_mutex);
			i++;
		}
		if (i == philo->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->data->check_end_mutex);
			philo->data->all_ate = 1;
			pthread_mutex_unlock(&philo->data->check_end_mutex);
			return (1);
		}
	}
	return (0);
}

int	check_for_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->data->meal_mutex);
		if (return_start_time(philo->data)
			- philo[i].last_meal_time > philo->data->time_to_die)
		{
			pthread_mutex_unlock(&philo->data->meal_mutex);
			pthread_mutex_lock(&philo->data->check_end_mutex);
			philo->data->phi_died = 1;
			pthread_mutex_unlock(&philo->data->check_end_mutex);
			pthread_mutex_lock(&philo->data->write_mutex);
			printf("%lu %d %s\n", return_start_time(philo->data), philo[i].id,
				"is dead");
			pthread_mutex_unlock(&philo->data->write_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->meal_mutex);
		i++;
	}
	return (0);
}

int	monitoring(t_philo *philo)
{
	while (1)
	{
		if (check_for_meals(philo))
			return (0);
		if (check_for_death(philo))
			return (0);
		usleep(100);
	}
}
