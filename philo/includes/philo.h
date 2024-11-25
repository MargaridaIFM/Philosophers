/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:12:42 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/25 23:36:25 by mfrancis         ###   ########.fr       */
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
#include <stdbool.h>

typedef struct s_info t_info;

typedef struct s_philo
{
    unsigned int	id;
    pthread_t 		theread_id;		
    pthread_mutex_t	*rigth_fork;
	pthread_mutex_t	*left_fork;
    unsigned int 	time_last_meal;
    unsigned int	meals_eaten;
   t_info 			*table; // TODO tirar ?
} t_philo;

typedef struct s_info
{
	unsigned int	start_time;
	unsigned int	nbr_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nbr_of_meals;
	unsigned int	died;  // TODO ou passar para int;
	unsigned int	all_eaten;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}               t_info;




// utils
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
unsigned int ft_my_time(void);

#endif