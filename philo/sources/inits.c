/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:14:55 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/26 21:23:03 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int init_table(int argc, char *argv[], t_info *table)
{
	table->nbr_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		table->nbr_of_meals = ft_atoi(argv[5]);
	if(table->time_to_die <= 0)
		return (-1);
	if(table->time_to_eat < 0 || table->time_to_sleep < 0)
		return(-1);
	if(table->nbr_philos < 1)
		return(-1);
	else if (table->nbr_philos == 1)
	{
		table->start_time = ft_my_time();
		printf("0 1 was taken a fork\n");
		usleep(table->time_to_die * 1000);
		printf("%zu 1 died\n", ft_my_time() - table->start_time);
		return(-1);
	}
	else if (table->nbr_philos % 2 != 0)
		table->time_to_think = 0.2 * ((2 * table->time_to_eat) - table->time_to_sleep);
	return(0);
}
int init_forks(t_info *table)
{
	int i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if(!table->forks)
		return(-1);
	while(table->nbr_philos > i)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
		//printf("criou mutex\n");
	}
	return(0);
}
