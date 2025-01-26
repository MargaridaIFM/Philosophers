/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:32:18 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/26 17:59:11 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Initializes philosopher threads and the monitor thread.
 *
 * If thread creation fails, it cleans up any already created threads.
 *
 * @param table Pointer to the table structure
 * @return 0 if all threads are successfully created, -1 otherwise.
 */
int	init_threads(t_info *table)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	table->start_time = ft_my_time();
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i].theread_id, NULL, &life_routine,
				&table->philos[i]) != 0)
		{
			error_pthread(table);
			j = 0;
			while (j++ < i)
				pthread_join(table->philos[j].theread_id, NULL);
			return (-1);
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &death_routine, table) != 0)
		error_pthread(table);
	if (threads_union(table) == -1)
		return (-1);
	return (0);
}
/**
 * @brief Joins all philosopher threads and the monitor thread.
 *
 * Waits for all philosopher and monitor threads to complete execution.
 *
 * @param table Pointer to the table structure.
 * @return 0 if all threads are successfully joined, -1 otherwise.
 */

int	threads_union(t_info *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i].theread_id, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 0)
		return (-1);
	return (0);
}

/**
 * @brief Routine executed by each philosopher thread.
 *
 * Simulates the lifecycle of a philosopher, including eating, sleeping, 
 * and thinking. The routine ends if the philosopher dies 
 * or if the simulation is terminated.
 *
 * @param arg Pointer to the philosopher structure.
 * @return NULL when the routine completes.
 */
void	*life_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	initial_usleep(philo);
	while (!is_dead(philo->table))
	{
		if (!take_forks(philo))
			break ;
		get_time_last_meal(philo);
		if (!act("is eating\n", philo, philo->table->time_to_eat))
		{
			pthread_mutex_unlock(philo->two_fork);
			pthread_mutex_unlock(philo->one_fork);
			break ;
		}
		meals_iteration(philo);
		pthread_mutex_unlock(philo->two_fork);
		pthread_mutex_unlock(philo->one_fork);
		if (!act("is sleeping\n", philo, philo->table->time_to_sleep))
			break ;
		if (!act("is thinking\n", philo, philo->table->time_to_think))
			break ;
	}
	return (NULL);
}
/**
 * @brief Routine for monitoring philosopher deaths and simulation termination.
 *
 * Continuously checks if any philosopher has died or if all philosophers 
 * have eaten the required number of meals.
 *
 * @param arg Pointer to the table structure.
 * @return NULL when the routine completes or a philosopher dies.
 */

void	*death_routine(void *arg)
{
	t_info			*table;
	unsigned int	i;

	table = (t_info *)arg;
	while (!table->extermination)
	{
		i = 0;
		pthread_mutex_lock(&table->life);
		while (table->nbr_philos > i)
		{
			if ((table->philos[i].time_last_meal) != 0 && (ft_my_time()
					- table->philos[i].time_last_meal) > table->time_to_die)
			{
				table->extermination = 1;
				dead_msg(table, &i);
				return (NULL);
			}
			i++;
		}
		if (extreminate_if(table))
			break ;
		else
			usleep(500);
	}
	return (NULL);
}
