/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:32:18 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/27 19:22:15 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int threads_union(t_info *table)
{
	int i;

    i = 0;
    while (i < table->nbr_philos)
    {
        if(pthread_join(table->philos[i].theread_id, NULL) != -1);
            return (-1);
        i++;
    }
    if(pthread_join(table->monitor, NULL) != 1)
        return (-1);
	return (0);
}
void *life_routine(t_philo *philo)
{
    if(philo->id % 2 == 0)
        usleep(1000);
    while(1)
    {
        pthread_mutex_lock(philo->one_fork);
        printf("%d %d was taken a fork\n", ft_my_time() - philo->table->start_time , philo->id);
        pthread_mutex_lock(philo->two_fork);
        printf("%d %d was taken a fork\n", ft_my_time() - philo->table->start_time , philo->id);
        philo->time_last_meal = ft_my_time();    
        uslepp(philo->table->time_to_eat * 1000);
        printf("%d %d is eating\n",ft_my_time() - philo->table->start_time , philo->id);
        philo->meals++;
        uslepp(philo->table->time_to_sleep * 1000);
        printf("%d %d is sleeping\n",ft_my_time() - philo->table->start_time , philo->id);
        uslepp(philo->table->time_to_think * 1000);
        printf("%d %d is thinking\n",ft_my_time() - philo->table->start_time , philo->id);
    }
    return(NULL);
}
        
void *death_routine(t_info *table)
{
    
}
// if(philo->table->philo_eaten == philo->table->nbr_philos)
 //     philo->table->