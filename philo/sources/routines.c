/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:32:18 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/27 20:52:16 by mfrancis         ###   ########.fr       */
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
void *life_routine(t_philo *philo) // funcao para proteger printf if excterminate = 1;
{
    if(philo->id % 2 == 0)
        usleep(1000);
    while(1)
    {
        pthread_mutex_lock(&philo->table->life);       
        if(philo->table->extermination)
        {
            pthread_mutex_unlock(&philo->table->life);       
            return (philo);   
        }
        pthread_mutex_unlock(&philo->table->life);       
        pthread_mutex_lock(philo->one_fork);
        printf("%d %d was taken a fork\n", ft_my_time() - philo->table->start_time , philo->id);
        pthread_mutex_lock(philo->two_fork);
        printf("%d %d was taken a fork\n", ft_my_time() - philo->table->start_time , philo->id);
        philo->time_last_meal = ft_my_time();    
        uslepp(philo->table->time_to_eat * 1000);
        printf("%d %d is eating\n",ft_my_time() - philo->table->start_time , philo->id);
        philo->meals_eaten++;
        uslepp(philo->table->time_to_sleep * 1000);
        printf("%d %d is sleeping\n",ft_my_time() - philo->table->start_time , philo->id);
        uslepp(philo->table->time_to_think * 1000);
        printf("%d %d is thinking\n",ft_my_time() - philo->table->start_time , philo->id);
    }
    return(NULL);
}
        
void *death_routine(t_info *table)
{
    int i;
 
    pthread_mutex_lock(&table->life);   
    pthread_mutex_unlock(&table->life);     
    while(!table->extermination)
    {
        i = 0;
        pthread_mutex_lock(&table->life);  
        while(table->nbr_philos > i)
        {
            if(table->philos[i].time_last_meal > table->time_to_eat)
            {
                table->extermination = 1;
                pthread_mutex_unlock(&table->life);
                return (NULL);
            }
            if(table->philos[i].meals_eaten == table->nbr_of_meals)
                table->philos_eaten++;
            i++;
        }
        if(philos_all_eaten(table) == -1)
            return(NULL);
        pthread_mutex_unlock(&table->life); 
    }
    return(NULL);
}

int philos_all_eaten(t_info *table)
{
    if(table->philos_eaten == table->nbr_of_meals)
    {
        table->extermination = 1;
        pthread_mutex_unlock(&table->life);
        return(-1);
    }
    return (0);
}
// if(philo->table->philo_eaten == philo->table->nbr_philos)
 //     philo->table->