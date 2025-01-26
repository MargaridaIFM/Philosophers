/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:37:05 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/26 01:00:10 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
