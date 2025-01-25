/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:32:18 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/25 23:51:39 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_threads(t_info *table)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	table->start_time = ft_my_time();
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i].theread_id, NULL, &life_routine,
				&table->philos[i]) != 0)
		{
			error_pthread(table);
			j = 0;
			while (j++ < i)
				pthread_join(table->philos[j].theread_id, NULL);
			return (-1);
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &death_routine, table) != 0)
		error_pthread(table);
	if (threads_union(table) == -1)
		return (-1);
	return (0);
}

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

void	*life_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	initial_usleep(philo);
	while (!is_dead(philo->table))
	{
		if (!take_forks(philo))
			break ;
		get_time_last_meal(philo);
		if (!act("is eating\n", philo, philo->table->time_to_eat))
		{
			pthread_mutex_unlock(philo->two_fork);
			pthread_mutex_unlock(philo->one_fork);
			break ;
		}
		meals_iteration(philo);
		pthread_mutex_unlock(philo->two_fork);
		pthread_mutex_unlock(philo->one_fork);
		if (!act("is sleeping\n", philo, philo->table->time_to_sleep))
			break ;
		if (!act("is thinking\n", philo, philo->table->time_to_think))
			break ;
	}
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
					- table->philos[i].time_last_meal) > table->time_to_die)
			{
				table->extermination = 1;
				dead_msg(table, &i);
				return (NULL);
			}
			i++;
		}
		if (extreminate_if(table))
			break ;
		else
			usleep(500);
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
// pthread_mutex_unlock(&philo->table->life);

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

// pthread_mutex_lock(&philo->table->life);
// philo->time_last_meal = ft_my_time();
// pthread_mutex_unlock(&philo->table->life);