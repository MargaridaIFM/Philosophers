/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:14:55 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/26 17:33:26 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief  This function ensures that all the fields in the `t_info` struct 
 * are initialized to zero or NULL to prevent undefined behavior.
 *
 * @param table Pointer to the t_info structure to be cleared.
 */
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

/**
 * @brief Initializes the t_info structure with the input parameters.
 * Check if all the input are greater than 0.
 * Also calculates the time to think for each philosopher.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Array of strings containing the arguments.
 * @param table Pointer to the t_info structure to be initialized.
 * @return 0 on success, -1 if an error occurs.
 */
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

/**
 * @brief Initializes the mutexes (forks) for the philosophers.
 *
 * Allocates memory for and initializes a mutex for each fork.
 *
 * @param table Pointer to the t_info structure
 * @return 0 on success, -1 if an error occurs.
 */
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

/**
 * @brief Creates mutexes for managing philosopher life, 
 * printing output, and tracking meals.
 *
 * @param table Pointer to the t_info structure 
 * @return 0 on success, -1 if an error occurs.
 */
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

/**
 * @brief Creates and initializes the philosopher structures
 * and assigns forks to each philosopher.
 *
 * @param table Pointer to the t_info structure
 */
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
