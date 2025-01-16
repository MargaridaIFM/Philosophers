/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:37:05 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/16 18:41:07 by mfrancis         ###   ########.fr       */
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

void	initial_usleep(unsigned int nbr_philos, unsigned int philo_id,
		unsigned int time_to_eat)
{
	if (nbr_philos % 2 == 0)
	{
		if (philo_id % 2 == 0)
			usleep(time_to_eat);
	}
	else
	{
		if (philo_id == nbr_philos)
			usleep(time_to_eat * 2);
		else if (philo_id % 2 == 0)
			usleep(time_to_eat);
	}
}

int	act(char *msg, t_philo *philo, unsigned int time)
{
	if (is_dead(philo->table))
		return (1);
	if (safe_printf(msg, philo->table, philo))
		return (0);
	usleep(time * 1000);
	return (2);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->one_fork);
		if (safe_printf("has taken a fork\n", philo->table, philo))
		{
			pthread_mutex_unlock(philo->one_fork);
			return (0);
		}
		pthread_mutex_lock(philo->two_fork);
		if (safe_printf("has taken a fork\n", philo->table, philo))
		{
			pthread_mutex_unlock(philo->two_fork);
			pthread_mutex_unlock(philo->one_fork);
			return (0);
		}
	}
	else
	{
		if (take_forks_impar(philo) == 0)
			return (0);
	}
	return (1);
}

int	is_dead(t_info *table)
{
	pthread_mutex_lock(&table->life);
	if (table->extermination)
	{
		pthread_mutex_unlock(&table->life);
		return (1);
	}
	pthread_mutex_unlock(&table->life);
	return (0);
}
	// pthread_mutex_lock(philo->one_fork);
		// if (safe_printf("has taken a fork\n", philo->table, philo))
		// {
		// 	pthread_mutex_unlock(philo->one_fork);
		// 	return (0);
		// }
		// pthread_mutex_lock(philo->two_fork);
		// if (safe_printf("has taken a fork\n", philo->table, philo))
		// {
		// 	pthread_mutex_unlock(philo->two_fork);
		// 	pthread_mutex_unlock(philo->one_fork);
		// 	return (0);
		// }