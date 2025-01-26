/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:53:22 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/26 17:39:13 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Frees all allocated resources and destroys mutexes in the simulation.
 *
 * @param table Pointer to the t_info structure.
 */

void	free_all(t_info *table)
{
	if (table->philos)
		free_philos(table);
	if (table->forks)
		free_forks(table);
	if (table->flag_life)
		pthread_mutex_destroy(&table->life);
	if (table->flag_print)
		pthread_mutex_destroy(&table->print);
	if (table->flag_meals)
		pthread_mutex_destroy(&table->meals);
}

/**
 * @brief Frees memory allocated for the philosophers and resets their fields.
 *
 * @param table Pointer to the t_info structure.
 */
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

/**
 * @brief Frees memory allocated for the forks and destroys their mutexes.
 *
 * @param table Pointer to the t_info structure.
 */
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
