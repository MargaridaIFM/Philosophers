/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:12:42 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/17 12:36:11 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>


typedef struct s_info
{
    int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}               t_info;

typedef struct s_philo
{
    /* data */
} t_philo;


#endif