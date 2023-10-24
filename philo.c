/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimina <mklimina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:57:26 by mklimina          #+#    #+#             */
/*   Updated: 2023/10/24 20:26:46 by mklimina         ###   ########.fr       */
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

long int return_start_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
t_data *init_data(char **argv, t_data *data, int argc)
{
	int i;
	i = 0;
	data -> number_of_philosophers = ft_atoi(argv[1]);
	data -> time_to_die= ft_atoi(argv[2]) ;
	data -> time_to_eat = ft_atoi(argv[3]);
	data -> time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data -> nb_must_eat = ft_atoi(argv[5]);
	data ->start_time = return_start_time();
	data -> all_ate = 0;
	data -> phi_died = 0;
	pthread_mutex_init(&data -> write_mutex, NULL);
	pthread_mutex_init(&data -> meal_mutex, NULL);
	pthread_mutex_init(&data -> check_end_mutex, NULL);
	// init array of the mutexes forks
	/*
	PHILO init 
	*/
	data -> philo = malloc(sizeof(t_philo *) * data -> number_of_philosophers);
	data -> forks = malloc(sizeof(pthread_mutex_t) * data -> number_of_philosophers);
	while(i < data -> number_of_philosophers)
	{
		pthread_mutex_init(&data -> forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data -> number_of_philosophers)
	{
		data -> philo[i] -> id = i + 1; 
		data -> philo[i] -> last_meal_time = 0;
		data -> philo[i] -> meal_counter = 0;
		data -> philo[i] -> data = data;
		if (data -> philo[i] -> id  % 2)
		{
			data -> philo[i] ->fork_one = &data->forks[(i + 1) % data -> number_of_philosophers];
			data -> philo[i] ->fork_two = &data->forks[i];
		}
		else
		{
			data -> philo[i] ->fork_one = &data->forks[i];
			data -> philo[i] ->fork_two = &data->forks[(i + 1) % data -> number_of_philosophers];
		}
		i++;
			
		 
	}
	
	
	return(data);
	
}
int	main(int argc, char **argv)
{
	t_data *data = malloc(sizeof(t_data));
	
	if (argc != 5 && argc != 6)
		return(0);
	data = init_data(argv, data, argc);
	printf("go philo\n");

}