/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:53:22 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/14 14:31:26 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_info *table)
{
	if (table->philos)
		free_philos(table);
	if (table->forks)
		free_forks(table);
	pthread_mutex_destroy(&table->life);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->meals);
	
}

void	free_philos(t_info *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		table->philos[i].one_fork = NULL;
		table->philos[i].two_fork = NULL;
		table->philos[i].table = NULL;
		i++;
	}
	free(table->philos);
}

void	free_forks(t_info *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	table->forks = NULL;
}
