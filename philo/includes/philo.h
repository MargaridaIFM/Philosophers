/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:12:42 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/12 10:48:46 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_info	t_info;

typedef struct s_philo
{
	unsigned int		id;
	pthread_t			theread_id;
	pthread_mutex_t		*one_fork;
	pthread_mutex_t		*two_fork;
	unsigned int		time_last_meal;
	unsigned int		meals_eaten;
	t_info				*table;
}						t_philo;

typedef struct s_info
{
	size_t				start_time;
	unsigned int		nbr_philos;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		time_to_think;
	unsigned int		nbr_of_meals;
	unsigned int		philos_eaten;
	pthread_mutex_t		*forks;
	t_philo				*philos;
	unsigned int		extermination;
	pthread_mutex_t		print;
	pthread_mutex_t		life;
	pthread_t			monitor;
}						t_info;

// inits
int						init_table(int argc, char *argv[], t_info *table);
int						init_forks(t_info *table);
int						init_monitor(t_info *table);
void					create_philos(t_info *table);
int						init_threads(t_info *table);

// routines
int						threads_union(t_info *table);
void					*life_routine(void *philo);
void					*death_routine(void *table);

// utils
void					ft_putstr_fd(char *s, int fd);
unsigned int			ft_my_time(void);
void					clean_mem(t_info *table);
unsigned int			ft_atoi(const char *nptr);
int						check_args(int argc, char *argv[]);

// errorr
void					free_all(t_info *table);
void					free_philos(t_info *table);
void					free_forks(t_info *table);

#endif