/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_routine_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:40:41 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/25 21:54:43 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// int	take_forks_impar(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->one_fork);
// 	if (safe_printf("has taken a fork\n", philo->table, philo))
// 	{
// 		pthread_mutex_unlock(philo->one_fork);
// 		return (0);
// 	}
// 	pthread_mutex_lock(philo->two_fork);
// 	if (safe_printf("has taken a fork\n", philo->table, philo))
// 	{
// 		pthread_mutex_unlock(philo->two_fork);
// 		pthread_mutex_unlock(philo->one_fork);
// 		return (0);
// 	}
// 	return (1);
// }

void	error_pthread(t_info *table)
{
	printf("ERROR: Failed creating thread\n");
	pthread_mutex_lock(&table->life);
	table->extermination = 1;
	pthread_mutex_unlock(&table->life);
}

int	extreminate_if(t_info *table)
{
	pthread_mutex_lock(&table->meals);
	if (table->philos_eaten == table->nbr_philos)
	{
		table->extermination = 1;
		pthread_mutex_unlock(&table->life);
		pthread_mutex_unlock(&table->meals);
		return (1);
	}
	pthread_mutex_unlock(&table->life);
	pthread_mutex_unlock(&table->meals);
	return (0);
}

void	dead_msg(t_info *table, unsigned int *i)
{
	pthread_mutex_unlock(&table->life);
	printf("%lu %d died\n", ft_my_time() - table->start_time,
		table->philos[*i].id);
}
