/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:12:42 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/26 14:52:59 by mfrancis         ###   ########.fr       */
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
    int	id;
    pthread_t 			theread_id;		
    pthread_mutex_t		*rigth_fork;
	pthread_mutex_t		*left_fork;
    int 				time_last_meal;
    int					meals_eaten;
   	t_info 				*table; // TODO tirar ?
} t_philo;

typedef struct s_info
{
	size_t			start_time;
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				nbr_of_meals;
	int				died;  // TODO ou passar para int;
	int				all_eaten;
	t_philo			*philos;
	pthread_mutex_t	*forks; // mesmo numero que philos
}               t_info;




// utils
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
unsigned int ft_my_time(void);

#endif