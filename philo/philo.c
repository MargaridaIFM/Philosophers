/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:30:56 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/17 18:48:51 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
Core concepts:
    [] process vs threads
    [] threads
    [] mutexes
    bonus:
        [] semaphores

[] structs:
    [] philo  - principal
        [] id (number);
        [] p_thread 
        [] mutex rigth_fork;
        [] mutex left_fork;
        [] time_last_meal;
        [] meals_eaten ?;
        [] t_info info;
        
[] #define ERROR_MSG;
        
        
    [] info
        [] present_time;
        [] nbr_of_philo;
        [] time_to_die;
        [] time_to_eat;
        [] time_to_sleep;
        [] nbr_of_meals;
        [] died ?;




Create the correct number of philosopher


Create the correct number of threads


Create a routine
    [] What each philosopher has to do ? In which order ?
        [] eat
        [] sleep
        [] think
        [] repeat
[] Initiate the threads with said routine
   
*/
