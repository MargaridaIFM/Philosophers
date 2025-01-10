/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:12:42 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/10 17:41:38 by mfrancis         ###   ########.fr       */
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
    int					id;
    pthread_t 			theread_id;		
    pthread_mutex_t		*one_fork;
	pthread_mutex_t		*two_fork;
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
	int				philos_eaten; 	
	pthread_mutex_t	*forks; // mesmo numero que philos
	t_philo			*philos;
	int				extermination; 
	pthread_mutex_t print;  	
	pthread_mutex_t life;
	pthread_t		monitor; 
}               t_info;


// 

// inits
int check_args(int argc, char *argv[]);
int init_table(int argc, char *argv[], t_info *table);
int init_forks_and_monitor(t_info *table);
void create_philos(t_info *table);
int init_threads(t_info *table);

// routines
int threads_union(t_info *table);
void *life_routine(void *philo);
void *death_routine(void *table);
// int	philos_all_eaten(t_info *table);

// utils
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
unsigned int ft_my_time(void);
void clean_mem(t_info *table);
int	ft_atoi(const char *nptr);

// errorr
void free_all(t_info *table);
void free_philos(t_info *table);
void free_forks(t_info *table);



#endif