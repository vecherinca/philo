/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:03:33 by mklimina          #+#    #+#             */
/*   Updated: 2023/11/02 21:01:24 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1 * sign;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	print_message(t_philo *philo, char *message)
{
	struct timeval	tv;

	pthread_mutex_lock(&philo->data->check_end_mutex);
	if (philo->data->all_ate == 1)
		return (pthread_mutex_unlock(&philo->data->check_end_mutex), 0);
	if (philo->data->phi_died == 1)
		return (pthread_mutex_unlock(&philo->data->check_end_mutex), 0);
	pthread_mutex_unlock(&philo->data->check_end_mutex);
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philo->data->write_mutex);
	printf("%lu %d %s\n", return_start_time(philo->data), philo->id, message);
	pthread_mutex_unlock(&philo->data->write_mutex);
	return (1);
}

int	ft_usleep(t_philo *philo, long int time)
{
	long int	start;

	start = return_start_time(philo->data);
	while ((return_start_time(philo->data) - start) < time)
	{
		pthread_mutex_lock(&philo->data->check_end_mutex);
		if (philo->data->all_ate == 1 || philo->data->phi_died == 1)
		{
			return (pthread_mutex_unlock(&philo->data->check_end_mutex), 0);
		}
		pthread_mutex_unlock(&philo->data->check_end_mutex);
		usleep(time / 10);
	}
	return (1);
}
