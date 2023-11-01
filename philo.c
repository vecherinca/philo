/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:57:26 by mklimina          #+#    #+#             */
/*   Updated: 2023/11/01 16:42:00 by mklimina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// thread_routine is the function the thread invokes right after its
// creation. The thread ends at the end of this function.
// void	*routine(void *data)
// {
// 	pthread_t tid;
// 	(void) data;
// 	// The pthread_self() function provides
// 	// this thread's own ID.
// 	tid = pthread_self();
// 	printf("%sThread [%ld]: The heaviest burden is to exist without living.%s\n",
// 		YELLOW, tid, NC);
// 	return (NULL); // The thread ends here.
// }

long int	return_start_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

t_data	*init_data(char **argv, t_data *data, int argc)
{
	int	i;

	i = 0;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) >= 0)
		data->nb_must_eat = ft_atoi(argv[5]);
	else
		data->nb_must_eat = -1;
	data->start_time = return_start_time();
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
	ft_printf("%u %d %s\n", return_start_time(), philo->id, message);
	pthread_mutex_unlock(&philo->data->write_mutex);
	return (1);
}

int	ft_usleep(t_philo *philo)
{
	long int	start;

	// CHECK IF NO ONE DIED
	start = return_start_time();
	while ((return_start_time() - start) < philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->check_end_mutex);
		if (philo->data->all_ate == 1)
			return (pthread_mutex_unlock(&philo->data->check_end_mutex), 0);
		if (philo->data->phi_died == 1)
			return (pthread_mutex_unlock(&philo->data->check_end_mutex), 0);
		pthread_mutex_unlock(&philo->data->check_end_mutex);
		usleep(philo->data->time_to_die / 10);
	}
	return (1);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_one);
	if (print_message(philo, TAKE_FORK) == 0)
		return (pthread_mutex_unlock(philo->fork_one), 0);
	pthread_mutex_lock(philo->fork_two);
	if (print_message(philo, TAKE_FORK) == 0)
		return (pthread_mutex_unlock(philo->fork_two),
			pthread_mutex_unlock(philo->fork_one), 0);
	if (print_message(philo, EATING) == 0)
		return (pthread_mutex_unlock(philo->fork_two),
			pthread_mutex_unlock(philo->fork_one), 0);
	if (ft_usleep(philo) == 0)
		return (pthread_mutex_unlock(philo->fork_two),
			pthread_mutex_unlock(philo->fork_one), 0);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = return_start_time();
	printf(
		"LAST TIME %ld\n", philo->last_meal_time);
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
	if (ft_usleep(philo) == 0)
		return (0);
	return (1);
}

int	to_think(t_philo *philo)
{
	if (print_message(philo, THINKING) == 0)
		return (0);
	if (ft_usleep(philo) == 0)
		return (0);
	return (1);
}

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (1)
	{
		if (eat(philo) == 0)
			return ((void *)0);
		if (sleep_philo(philo) == 0)
			return ((void *)0);
		if (to_think(philo) == 0)
			return ((void *)0);
	}
	return ((void *)1);
}
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
		j = 0;
		while (j < philo->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->data->meal_mutex);
			if (return_start_time()
				- philo[i].last_meal_time > philo->data->time_to_die)
			{
				printf(
					"LAST TIME %ld\n", philo[j].last_meal_time);
				pthread_mutex_unlock(&philo->data->meal_mutex);
				print_message(philo, DEAD);
				pthread_mutex_lock(&philo->data->check_end_mutex);
				philo->data->phi_died = 1;
				pthread_mutex_unlock(&philo->data->check_end_mutex);
				return (0);
			}
			pthread_mutex_unlock(&philo->data->meal_mutex);
			j++;
		}
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	t_data *data = malloc(sizeof(t_data));

	if (argc != 5 && argc != 6)
		return (0);
	data = init_data(argv, data, argc);

	int i;
	i = 0;

	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&(data->philo[i].thread), NULL, &routine,
				&data->philo[i]))
			printf("ERROR THREAD CREATING\n");
		i++;
	}
	monitoring(data->philo);
	i = 0;

	while (i < data->number_of_philosophers)
	{
		// do we put something instad of NULL?
		if (pthread_join((data->philo[i].thread), NULL))
			printf("ERROR THREAD CREATING\n");
		i++;
	}
}