/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_routine_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:40:41 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/26 17:36:08 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Handles errors related to thread creation and sets
 * the extermination flag to indicate that the simulation should terminate.
 *
 * @param table Pointer to the t_info structure.
 */
void	error_pthread(t_info *table)
{
	printf("ERROR: Failed creating thread\n");
	pthread_mutex_lock(&table->life);
	table->extermination = 1;
	pthread_mutex_unlock(&table->life);
}

/**
 * @brief Checks if all philosophers have eaten the required number of meals.

 *
 * @param table Pointer to the t_info structure 
 * @return 1 if all philosophers have eaten the required meals, 0 otherwise.
 */

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
/**
 * @brief Prints a message indicating that a philosopher has died.
 *
 * @param table Pointer to the t_info structure 
 * @param i Pointer to the index of the philosopher who has died.
 */

void	dead_msg(t_info *table, unsigned int *i)
{
	pthread_mutex_unlock(&table->life);
	printf("%lu %d died\n", ft_my_time() - table->start_time,
		table->philos[*i].id);
}
