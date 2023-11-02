/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:58:51 by mklimina          #+#    #+#             */
/*   Updated: 2023/11/02 21:15:31 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_one);
	if (print_message(philo, TAKE_FORK) == 0
		|| philo->data->number_of_philosophers == 1)
		return (pthread_mutex_unlock(philo->fork_one), 0);
	pthread_mutex_lock(philo->fork_two);
	if (print_message(philo, TAKE_FORK) == 0)
		return (pthread_mutex_unlock(philo->fork_two),
				pthread_mutex_unlock(philo->fork_one),
				0);
	if (print_message(philo, EATING) == 0)
		return (pthread_mutex_unlock(philo->fork_two),
				pthread_mutex_unlock(philo->fork_one),
				0);
	if (ft_usleep(philo, philo->data->time_to_eat) == 0)
		return (pthread_mutex_unlock(philo->fork_two),
				pthread_mutex_unlock(philo->fork_one),
				0);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = actual_time();
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_unlock(philo->fork_two);
	pthread_mutex_unlock(philo->fork_one);
	return (1);
}

int	sleep_philo(t_philo *philo)
{
	if (print_message(philo, SLEEPING) == 0)
		return (0);
	if (ft_usleep(philo, philo->data->time_to_sleep) == 0)
		return (0);
	return (1);
}

int	to_think(t_philo *philo)
{
	if (print_message(philo, THINKING) == 0)
		return (0);
	return (1);
}