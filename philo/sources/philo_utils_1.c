/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:37:05 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/13 19:53:54 by mfrancis         ###   ########.fr       */
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

int	act(char *msg, t_philo *philo)
{
	if (safe_printf(msg, philo->table, philo))
		return (0);
	usleep(philo->table->time_to_think * 1000);
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->two_fork);
		if (safe_printf("has taken a fork\n", philo->table, philo))
			return (0);
		pthread_mutex_lock(philo->one_fork);
		if (safe_printf("has taken a fork\n", philo->table, philo))
			return (0);
	}
	else
	{
		pthread_mutex_lock(philo->one_fork);
		if (safe_printf("has taken a fork\n", philo->table, philo))
			return (0);
		pthread_mutex_lock(philo->two_fork);
		if (safe_printf("has taken a fork\n", philo->table, philo))
			return (0);
	}
	return (1);
}

int	is_dead(pthread_mutex_t *life_mutex,
	unsigned int status)
{
	pthread_mutex_lock(life_mutex);
	if (status)
	{
		pthread_mutex_unlock(life_mutex);
		return (1);
	}
	pthread_mutex_unlock(life_mutex);
	return (0);
}
