/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:14:55 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/25 21:54:59 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_mem(t_info *table)
{
	table->start_time = 0;
	table->nbr_philos = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->time_to_think = 0;
	table->nbr_of_meals = 0;
	table->extermination = 0;
	table->philos_eaten = 0;
	table->philos = NULL;
	table->forks = NULL;
	table->monitor = 0;
	table->flag_meals = 0;
	table->flag_print = 0;
	table->flag_life = 0;
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
		|| table->time_to_sleep == 0 || table->nbr_philos == 0)
		return (-1);
	if (table->nbr_philos == 1)
	{
		usleep(table->time_to_die * 1000);
		printf("0 1 was taken a fork\n%d 1 died\n", table->time_to_die);
		return (-1);
	}
	else
		table->time_to_think = get_time_think(table->nbr_philos,
				table->time_to_sleep, table->time_to_eat);
	return (0);
}

int	init_forks(t_info *table)
{
	unsigned int	i;

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
	return (0);
}

int	init_monitor(t_info *table)
{
	if (pthread_mutex_init(&table->life, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	table->flag_life = 1;
	if (pthread_mutex_init(&table->print, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	table->flag_print = 1;
	if (pthread_mutex_init(&table->meals, NULL) != 0)
	{
		ft_putstr_fd("ERROR: Failed creating mutex\n", 2);
		return (-1);
	}
	table->flag_meals = 1;
	return (0);
}

void	create_philos(t_info *table)
{
	unsigned int	idx;

	idx = 0;
	while (table->nbr_philos > idx)
	{
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

		// printf("ERROR: Failed creating thread for monitor\n");
		// pthread_mutex_lock(&table->life);
		// table->extermination = 1;
		// pthread_mutex_unlock(&table->life);
	/* if (table->nbr_philos % 2 == 0)
	{
		if (table->time_to_eat > table->time_to_sleep)
			table->time_to_think = table->time_to_eat - table->time_to_sleep;
		else
			table->time_to_think = 0;
	}
	else
	{
		if (table->time_to_eat * 2 > table->time_to_sleep)
			table->time_to_think = table->time_to_eat * 2
				- table->time_to_sleep;
		else
			table->time_to_think = 0;
	} */