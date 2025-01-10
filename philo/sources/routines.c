/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:32:18 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/10 18:25:26 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	threads_union(t_info *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i].theread_id, NULL) != -1)
			return (-1);
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 1)
		return (-1);
	return (0);
}
		// funcao para proteger printf if excterminate = 1;


int safe_printf(char *msg, t_info *table, t_philo *philo)
{
	pthread_mutex_lock(&table->print);
	if (table->extermination == 0)
	{
		printf("%lu %d ", ft_my_time() - philo->table->start_time,
			philo->id);
		printf("%s", msg);
		pthread_mutex_unlock(&table->print);
		return(0);
	}
	pthread_mutex_unlock(&table->print);
	return(1);
}

void	*life_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;

	if(philo->table->nbr_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(philo->table->time_to_eat);
	}
	else
	{
		if (philo->id == philo->table->nbr_philos)
		{
			usleep(philo->table->time_to_eat * 2);
		}
		else if (philo->id % 2 == 0)
		{
			usleep(philo->table->time_to_eat);
		}
	}
	while (1)
	{
		pthread_mutex_lock(&philo->table->life);
		if (philo->table->extermination)
		{
			pthread_mutex_unlock(&philo->table->life);
			return (philo);
		}
		pthread_mutex_unlock(&philo->table->life);
		if(philo->id  % 2 == 0)
		{
			pthread_mutex_lock(philo->two_fork);
			if (safe_printf("has taken a fork\n", philo->table, philo))
				break ;
			pthread_mutex_lock(philo->one_fork);
			if (safe_printf("has taken a fork\n", philo->table, philo))
				break ;
		}
		else
		{
			pthread_mutex_lock(philo->one_fork);
			if (safe_printf("has taken a fork\n", philo->table, philo))
				break ;
			pthread_mutex_lock(philo->two_fork);
			if (safe_printf("has taken a fork\n", philo->table, philo))
				break ;
		}
		philo->time_last_meal = ft_my_time();
		if (safe_printf("is eating\n", philo->table, philo))
				break ;
		usleep(philo->table->time_to_eat * 1000);
		philo->meals_eaten++;
		if (safe_printf("is sleeping\n", philo->table, philo))
				break ;
		pthread_mutex_unlock(philo->two_fork);
		pthread_mutex_unlock(philo->one_fork);
		usleep(philo->table->time_to_sleep * 1000);
		if (safe_printf("is thinking\n", philo->table, philo))
				break ;
		usleep(philo->table->time_to_think * 1000);
	}
	pthread_mutex_unlock(philo->two_fork);
	pthread_mutex_unlock(philo->one_fork);
	return (NULL);
}


void	*death_routine(void *arg)
{
	t_info *table;
	table= (t_info *)arg;
	int	i;

	//pthread_mutex_lock(&table->life);
	//pthread_mutex_unlock(&table->life);
	while (!table->extermination)
	{
		i = 0;
		pthread_mutex_lock(&table->life);
		while (table->nbr_philos > i)
		{
			if ((table->philos[i].time_last_meal) != 0 && (ft_my_time() - (unsigned int)(table->philos[i].time_last_meal)) > (unsigned int)table->time_to_die)
			{
				table->extermination = 1;
				// passar p safe_printf;
				pthread_mutex_unlock(&table->life);
				printf("%lu %d died\n", ft_my_time() - table->start_time, table->philos[i].id);
				return (NULL);
			}
			if (table->philos[i].meals_eaten == table->nbr_of_meals)
				table->philos_eaten++;
			i++;
		}
		if (table->philos_eaten == table->nbr_of_meals)
		{
			table->extermination = 1;
			pthread_mutex_unlock(&table->life);
			return (NULL);
		}	
		pthread_mutex_unlock(&table->life);
	}
	return (NULL);
}
// int leave_table(t_info *table)
// {
// 	free_all(table);
// }
// int	philos_all_eaten(t_info *table)
// {
// 	if (table->philos_eaten == table->nbr_of_meals)
// 	{
		

// 		return (-1);
// 	}
// 	return (0);
// }
// if(philo->table->philo_eaten == philo->table->nbr_philos)
//     philo->table->