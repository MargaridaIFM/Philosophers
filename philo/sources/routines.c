/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:32:18 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/14 19:10:45 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	threads_union(t_info *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i].theread_id, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 0)
		return (-1);
	return (0);
}

unsigned int	safe_printf(char *msg, t_info *table, t_philo *philo)
{
	pthread_mutex_lock(&table->print);
	if (table->extermination == 0)
	{
		printf("%lu %d ", ft_my_time() - philo->table->start_time, philo->id);
		printf("%s", msg);
		pthread_mutex_unlock(&table->print);
		return (0);
	}
	pthread_mutex_unlock(&table->print);
	return (1);
}
void	meals_iteration(t_philo *philo)
{
	// pthread_mutex_lock(&table->meals);
	// meals_eaten++;
	// if (meals_eaten == table->nbr_of_meals)
	// 	table->philos_eaten++;
	// pthread_mutex_unlock(&table->meals);
		pthread_mutex_lock(&philo->table->meals);
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->table->nbr_of_meals)
				philo->table->philos_eaten++;
		pthread_mutex_unlock(&philo->table->meals);
}

void	*life_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	initial_usleep(philo->table->nbr_philos, philo->id,
		philo->table->time_to_eat);
	while (1)
	{
		if (is_dead(&philo->table->life, philo->table->extermination))
			break ;
		if (!take_forks(philo))
			break ;
		philo->time_last_meal = ft_my_time();
		if (!act("is eating\n", philo, philo->table->time_to_eat))
			break ;
		meals_iteration(philo);
		pthread_mutex_unlock(philo->two_fork);
		pthread_mutex_unlock(philo->one_fork);
		pthread_mutex_lock(&philo->table->life);
		if (is_dead(&philo->table->life, philo->table->extermination)
			|| !act("is sleeping\n", philo, philo->table->time_to_sleep)
			|| !act("is thinking\n", philo, philo->table->time_to_think))
			{
				pthread_mutex_unlock(&philo->table->life);
				return (NULL);
			}
		pthread_mutex_unlock(&philo->table->life);
		
	}
	pthread_mutex_unlock(philo->two_fork);
	pthread_mutex_unlock(philo->one_fork);
	return (NULL);
}

void	*death_routine(void *arg)
{
	t_info			*table;
	unsigned int	i;

	table = (t_info *)arg;
	while (!table->extermination)
	{
		i = 0;
		pthread_mutex_lock(&table->life);
		while (table->nbr_philos > i)
		{
			if ((table->philos[i].time_last_meal) != 0 && (ft_my_time()
					- (table->philos[i].time_last_meal)) > table->time_to_die)
			{
				table->extermination = 1;
				pthread_mutex_unlock(&table->life);
				printf("%lu %d died\n", ft_my_time() - table->start_time,
					table->philos[i].id);
				return (NULL);
			}
			i++;
		}
		if (table->philos_eaten == table->nbr_philos)
		{
			table->extermination = 1;
			pthread_mutex_unlock(&table->life);
			return (NULL);
		}
		pthread_mutex_unlock(&table->life);
	}
	return (NULL);
}

	/* if (philo->table->nbr_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(philo->table->time_to_eat);
	}
	else
	{
		if (philo->id == philo->table->nbr_philos)
			usleep(philo->table->time_to_eat * 2);
		else if (philo->id % 2 == 0)
			usleep(philo->table->time_to_eat);
	} */

		// pthread_mutex_lock(&philo->table->life);
		// if (philo->table->extermination)
		// {
		// 	pthread_mutex_unlock(&philo->table->life);
		// 	break ;
		// }
		//pthread_mutex_unlock(&philo->table->life);

		// if (philo->id % 2 == 0)
		// {
		// 	pthread_mutex_lock(philo->two_fork);
		// 	if (safe_printf("has taken a fork\n", philo->table, philo))
		// 		break ;
		// 	pthread_mutex_lock(philo->one_fork);
		// 	if (safe_printf("has taken a fork\n", philo->table, philo))
		// 		break ;
		// }
		// else
		// {
		// 	pthread_mutex_lock(philo->one_fork);
		// 	if (safe_printf("has taken a fork\n", philo->table, philo))
		// 		break ;
		// 	pthread_mutex_lock(philo->two_fork);
		// 	if (safe_printf("has taken a fork\n", philo->table, philo))
		// 		break ;
		// }