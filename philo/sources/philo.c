/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:30:56 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/26 17:33:11 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Entry point of the program to initialize and manage the philosopher
 * simulation.
 *
 * It validates the arguments, initializes resources (such as tables and forks),
 * and manages the creation and execution of threads for each philosopher. 
 * In case of an error, it frees allocated resources.
 * @param argc Number of arguments passed to the program.
 * @param argv Array of strings containing the arguments. Expected:
 *             - argv[1]: Number of philosophers.
 *             - argv[2]: Time to die (in milliseconds).
 *             - argv[3]: Time to eat (in milliseconds).
 *             - argv[4]: Time to sleep (in milliseconds).
 *             - argv[5]: Optional number of times each philosopher must eat.
 * @return Returns 0 if the execution is successful or other number 
 * if an error occurs.
 */

int	main(int argc, char *argv[])
{
	t_info	table;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("ERROR: Wrong number of elements\n", 2), 1);
	clean_mem(&table);
	if (check_args(argc, argv) == -1 || init_table(argc, argv, &table) == -1
		|| init_forks(&table) == -1 || init_monitor(&table) == -1)
	{
		free_all(&table);
		return (2);
	}
	table.philos = malloc(sizeof(t_philo) * table.nbr_philos);
	if (!table.philos)
	{
		free_all(&table);
		return (3);
	}
	create_philos(&table);
	if (init_threads(&table) == -1)
	{
		free_all(&table);
		return (4);
	}
	free_all(&table);
	return (0);
}

/*
[x] main

	[x] check the nbr of args;
		[x] if argc != 5 && argc != 6
			[x] return error message;
	
	[x] clean initial memory;
	
	[x] check args
		[x] check format - only numbers;
	
	[x]  init_table
		[x] atoi
			[x] check if the number is positive and != 0;
		[] check nbr of philos;
			[] if nbr_philos == 1
				[]print 0 1 was taken a fork\n%d 1 died\n"
				[] end program;
			[] else 
				[] calculate time_to_think;

	[] init_forks
		[x] malloc sizof(mutex) * nrb_philos;
		[x] while nbr_philos > 0
			[x] mutex_init forks[i];
	
	[] init_monitor
		[x] flag_life = 1;
		[x] mutex_init life;
		[x] flag_print = 1;
		[x] mutex_init print;
		[x] flag_meals = 1;
		[x] mutex_init meals;
	[x]philos = malloc(sizeof(table->philo) * table->nbr_of_philos));
	
	[x] create philos
		[x] while()
			[x]id = idx + 1;
			[x] info 0;
			[x] pointer p a table;
			[x]  fork assigment 
				[x]if philo = 0
					[x]two_fork[table->nbr_philos - 1];
				[x]else
					[x] pointer p two_fork; - forks[idx - 1;
				[x] pointer p one_fork; - forks[idx];

	[x] init_threads; 
		[x] while(nbr_philos)
			[x] p_thread_create(table->philo->theread_id, routine, table->philo);
		[x] p_thread_create(table->monitor, monitor_routine, table);
		[x] threads_union(table) 
			[x] while(nbr_philos)
				[x] p_thread_join(table->philo[i]->theread_id);
			[x] p_thread_join(table->monitor);

	[x] free_all
		[x] free philos;
		[x] free forks;
		[x] destroy mutex life;
		[x] destroy mutex print;
		[x] destroy mutex meals;

[x] life_routine
	[x] initial usleep
		[x] if nbr_philos is even or not
	[x] while is not dead
			[x] check is_dead
				[x] if is_dead
					[x] return NULL;
					
	[x] take_forks
		[x] mutex_lock;
		[x] mutex_lock;
		[x] if is_dead
			[x] mutex_unlock;
			[x] mutex_unlock;
			[x] return 0;
			
	[x] get_time_last_meal
		[x] time_last_meal = get_my_time;
	
	[x] act
		[x] print message;
		[x] while time
			[x] small usleep;
			[x] check is_dead
				
	[x] meals_iteration
		[x] mutex_unlock;
		[x] meals_eaten++;
		[x] mutex_unlock;


[x] death_routine
	[x] mutex_lock;
	[x] check if each of philos time_last_meal > time_to_die
		[x] if yes
			[x] flag extermination = 1
			[x] print dead message;
			[x] return NULL;
	[x] if philos have eaten the nbr_of_meals (argc == 6)
			[x] flag extermination = 1;
	[x] else
		[x] usleep(1000)for monitor rest;

*/