/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:37:05 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/26 17:51:35 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Calculates the time a philosopher should spend thinking.
 *
 * @param nbr_philos Number of philosophers 
 * @param time_to_sleep Time sleeping (in milliseconds) 
 * @param time_to_eat Time eating (in milliseconds)
 * @return Thinking time in milliseconds.
 */
unsigned int	get_time_think(unsigned int nbr_philos,
		unsigned int time_to_sleep, unsigned int time_to_eat)
{
	if (nbr_philos % 2 == 0)
	{
		if (time_to_eat > time_to_sleep)
			return (time_to_eat - time_to_sleep);
		return (0);
	}
	else
	{
		if (time_to_eat * 2 > time_to_sleep)
			return (time_to_eat * 2 - time_to_sleep);
		return (0);
	}
}

/**
 * @brief Introduces an initial delay for philosophers to stagger their actions.

 *
 * @param philo Pointer to the philosopher structure.
 * @return Always returns 1 after applying the delay.
 */
int	initial_usleep(t_philo *philo)
{
	if (philo->table->nbr_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(philo->table->time_to_eat);
	}
	else
	{
		if (philo->id == philo->table->nbr_philos)
			usleep(philo->table->time_to_eat * 2);
		else if (philo->id % 2 == 0)
			usleep(philo->table->time_to_eat);
	}
	return (1);
}

/**
 * @brief Prints a message to the console in a thread-safe manner.
 *
 * Locks the `print` and `life` mutexes to ensure synchronized access 
 * to shared dataand console output.
 *
 * @param msg The message to be printed
 * @param table Pointer to the t_info structure 
 * @param philo Pointer to the philosopher 
 * @return 0 in case of success, 1 otherwise.
 */
unsigned int	safe_printf(char *msg, t_info *table, t_philo *philo)
{
	pthread_mutex_lock(&table->print);
	pthread_mutex_lock(&table->life);
	if (table->extermination == 0)
	{
		printf("%lu %d ", ft_my_time() - philo->table->start_time, philo->id);
		printf("%s", msg);
		pthread_mutex_unlock(&table->life);
		pthread_mutex_unlock(&table->print);
		return (0);
	}
	pthread_mutex_unlock(&table->life);
	pthread_mutex_unlock(&table->print);
	return (1);
}

/**
 * @brief Determines the order in which a philosopher should pick up forks.
 *
 * Ensures that the philosopher always locks the smaller-addressed fork first 
 * to avoid potential deadlocks. 
 * Assigns the forks to the provided pointers in the correct order.
 *
 * @param philo Pointer to the philosopher structure.
 * @param fork_one Pointer to store the first fork to be locked.
 * @param fork_two Pointer to store the second fork to be locked.
 */
void	choose_forks(t_philo *philo, pthread_mutex_t **fork_one,
		pthread_mutex_t **fork_two)
{
	if (philo->one_fork > philo->two_fork)
	{
		*fork_one = philo->two_fork;
		*fork_two = philo->one_fork;
	}
	else
	{
		*fork_one = philo->one_fork;
		*fork_two = philo->two_fork;
	}
}
