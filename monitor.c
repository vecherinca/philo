/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:58:15 by mklimina          #+#    #+#             */
/*   Updated: 2023/11/03 01:09:37 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_philo *philo)
{
	int	i;
	int	j;

	while (1)
	{
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
				return (0);
			}
		}
		j = -1;
		while (++j < philo->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->data->meal_mutex);
			if (return_start_time(philo->data)
				- philo[j].last_meal_time > philo->data->time_to_die)
			{
				pthread_mutex_unlock(&philo->data->meal_mutex);
				print_message(philo, DEAD);
				pthread_mutex_lock(&philo->data->check_end_mutex);
				philo->data->phi_died = 1;
				pthread_mutex_unlock(&philo->data->check_end_mutex);
				return (0);
			}
			pthread_mutex_unlock(&philo->data->meal_mutex);
		}
		usleep(100);
	}
}
