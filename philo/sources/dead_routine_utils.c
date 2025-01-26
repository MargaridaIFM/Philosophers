/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_routine_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:40:41 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/26 01:00:36 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
