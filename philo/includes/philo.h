/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:12:42 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/25 23:42:33 by mfrancis         ###   ########.fr       */
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
	pthread_mutex_t		meals;
	pthread_t			monitor;
	int					flag_life;
	int					flag_meals;
	int					flag_print;
}						t_info;

// inits
void			clean_mem(t_info *table);
int				init_table(int argc, char *argv[], t_info *table);
int				init_forks(t_info *table);
int				init_monitor(t_info *table);
void			create_philos(t_info *table);

// routines
int				init_threads(t_info *table);
int				threads_union(t_info *table);
void			*life_routine(void *philo);
void			*death_routine(void *table);

// utils
void			ft_putstr_fd(char *s, int fd);
unsigned int	ft_my_time(void);
unsigned int	ft_atoi(const char *nptr);
int				check_args(int argc, char *argv[]);

// utils_1
unsigned int	get_time_think(unsigned int nbr_philos,
					unsigned int time_to_sleep, unsigned int time_to_eat);
int				initial_usleep(t_philo *philo);	
unsigned int	safe_printf(char *msg, t_info *table, t_philo *philo);
void			choose_forks(t_philo *philo, pthread_mutex_t **fork_one,
					pthread_mutex_t **fork_two);
int				ft_my_usleep(size_t milliseconds);
// dead_routine_utils
void			error_pthread(t_info *table);
int				extreminate_if(t_info *table);
void			dead_msg(t_info *table, unsigned int *i);

// life_routine_utils
int				is_dead(t_info *table);
int				take_forks(t_philo *philo);
void			get_time_last_meal(t_philo *philo);
int				act(char *msg, t_philo *philo, unsigned int time);
void			meals_iteration(t_philo *philo);

// errorr
void			free_all(t_info *table);
void			free_philos(t_info *table);
void			free_forks(t_info *table);

#endif