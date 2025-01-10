/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:14:55 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/10 17:48:23 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
			{
				ft_putstr_fd("ERROR: Invalid format!\n", 2);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

int	init_table(int argc, char *argv[], t_info *table)
{
	table->nbr_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		table->nbr_of_meals = ft_atoi(argv[5]);
		if (table->nbr_of_meals == 0)
			return (-1);
	}
	if (table->time_to_die == 0 || table->time_to_eat == 0
		|| table->time_to_sleep == 0 || table->nbr_philos < 1)
		return (-1);
	if (table->nbr_philos == 1)
	{
		usleep(table->time_to_die * 1000);
		printf("0 1 was taken a fork\n%d 1 died\n", table->time_to_die);
		return (-1);
	}
	else if (table->nbr_philos % 2 == 0)
	{
		if(table->time_to_eat > table->time_to_sleep)
			table->time_to_think = table->time_to_eat - table->time_to_sleep;
		else
			table->time_to_think = 0;
	}
	else
	{
		if(table->time_to_eat * 2 > table->time_to_sleep)
			table->time_to_think = table->time_to_eat * 2 - table->time_to_sleep;
		else
			table->time_to_think = 0;
	}

	return (0);
}
int	init_forks_and_monitor(t_info *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (!table->forks)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	while (table->nbr_philos > i)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&table->life, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	if (pthread_mutex_init(&table->print, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	return (0);
}

void	create_philos(t_info *table)
{
	int	idx;

	idx = 0;
	// printf("nbr of philos %d\n", table->nbr_philos);
	while (table->nbr_philos > idx)
	{
		// printf("Aqui %d\n", idx);
		table->philos[idx].id = idx + 1;
		table->philos[idx].meals_eaten = 0;
		table->philos[idx].time_last_meal = 0;
		table->philos[idx].table = table;
		table->philos[idx].theread_id = 0;
		if (table->philos[idx].id == 1)
			table->philos[0].two_fork = &table->forks[table->nbr_philos - 1];
		else
			table->philos[idx].two_fork = &table->forks[idx - 1];
		table->philos[idx].one_fork = &table->forks[idx];
		idx++;
	}
}
int	init_threads(t_info *table)
{
	int	i;

	i = 0;
	table->start_time = ft_my_time();
	pthread_mutex_lock(&table->life);
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i].theread_id, NULL, &life_routine, &table->philos[i]) != 0)
		{
			free_all(table);
			printf("ERROR: Failed creating thread for philos\n");
			return (-1);
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &death_routine,
			table) != 0)
	{
		free_all(table);
		printf("ERROR: Failed creating thread for monitot\n");
		return (-1);
	}
	pthread_mutex_unlock(&table->life);
	if (threads_union(table) == -1)
		return (-1);
	return (0);
}

// void create_philos(t_info *table)
// {
// 	int idx;

// 	idx = 1;
// 	while(table->nbr_philos >= idx)
// 	{
// 		table->philos[idx - 1].id = idx;
// 		printf("id: %d\n", table->philos[idx - 1].id);

// 		table->philos[idx - 1 ].meals_eaten = 0;
// 		printf("meals eaten: %d\n", table->philos[idx - 1].meals_eaten);
// 		table->philos[idx - 1].time_last_meal = 0;
// 		printf("time last meal: %d\n", table->philos[idx-1].time_last_meal);
// 		table->philos[idx - 1].table = table;
// 		//printf("table pointer philo: %p\n", table->philos[idx-1].table);
// 		//printf("table pointer: %p\n", table);
// 		table->philos[idx - 1].theread_id = 0;
// 		printf("thread_id: %lu\n", table->philos[idx-1].theread_id);
// 		if(table->philos[idx - 1].id == 1)
// 		{
// 			table->philos[0].two_fork = &table->forks[table->nbr_philos - 1];
// 			printf("pointer fork two: %p\n", &table->forks[table->nbr_philos
//				- 1]);
//
// 		}
// 		else
// 		{
// 			table->philos[idx - 1].two_fork = &table->forks[idx - 2];
// 			printf("pointer fork two: %p\n", &table->forks[idx - 2]);
// 		}
// 		table->philos[idx - 1].one_fork = &table->forks[idx - 1];
// 		printf("pointer fork one: %p\n", &table->forks[idx - 1]);
// 		idx++;
// 	}
// }
