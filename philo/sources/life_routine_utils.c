/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_routine_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:40:42 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/25 23:52:48 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*fork_one;
	pthread_mutex_t	*fork_two;

	choose_forks(philo, &fork_one, &fork_two);
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(fork_one);
	if (safe_printf("has taken a fork\n", philo->table, philo))
	{
		pthread_mutex_unlock(fork_one);
		return (0);
	}
	pthread_mutex_lock(fork_two);
	if (safe_printf("has taken a fork\n", philo->table, philo))
	{
		pthread_mutex_unlock(fork_two);
		pthread_mutex_unlock(fork_one);
		return (0);
	}
	return (1);
}

void	get_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->life);
	philo->time_last_meal = ft_my_time();
	pthread_mutex_unlock(&philo->table->life);
}

int	act(char *msg, t_philo *philo, unsigned int time)
{
	unsigned int	elapsed_time;
	unsigned int	interval;

	elapsed_time = 0;
	interval = 10;
	if (is_dead(philo->table))
		return (0);
	if (safe_printf(msg, philo->table, philo))
		return (0);
	while (elapsed_time < time)
	{
		usleep(interval * 1000);
		elapsed_time += interval;
		if (is_dead(philo->table))
			return (0);
	}
	return (1);
}

void	meals_iteration(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meals);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table->nbr_of_meals)
		philo->table->philos_eaten++;
	pthread_mutex_unlock(&philo->table->meals);
}
