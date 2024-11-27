/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:30:56 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/27 19:37:11 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_info	table;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("ERROR: Wrong number of elements\n", 2);
		return (0); // nao podes usar o exit
	}
	clean_mem(&table);
	if (check_args(argc, argv) == -1 || init_table(argc, argv, &table) == -1
		|| init_forks_and_monitor(&table) == -1)
		return (0); // messagem de erro ?
	table.philos = malloc(sizeof(t_philo) * table.nbr_philos);
	if (!table.philos)
		return (0); // mesagem de erro ?
	create_philos(&table);
	if (init_threads(&table) == -1)
	 	return (0);
	free_all(&table);
	return (0);
}

/*
! [] IMPORTANTE
	TODO [] exit is not allowed;
	[] getter - pesquisar
	[] setter - pesquisar

[x] clean initial memory;
[x] check args[] check nbr of philos (parsing) and // TODO init table
	[x] check nbr of philos
		[x]if nbr_philos == 1
			[x] wait x time and return(0); // ?
	[x] atoi for only positiv numbers;
	[x] check args > 0 && time_to_sleep >= 0;
	// [] //TODO (get_my_time) ?

// [] init_table
// 	[] start_time ? //! (get_my_time)
//  	[] args na info
[] init_forks
	[x] malloc sizof(mutex) * nrb_philos;
	[x] while
		[x] mutex forks[i];

[x]philos = malloc(sizeof(table->philo) * table->nbr_of_philos));
[] create philos
	[x] while()
		[x]id = idx
		[x] info 0;
		[x] pointer p a table;
		[]  fork assigment - mutex rigth and left
				[x]if philo = 0
					[x]two_fork[nrb_philos];
				[x]else
					[x] pointer p two_fork; - forks[nbr_philos] + 1;
			[x] pointer p one_fork; - forks[nbr_philos] - 1;


[] init_threads; //? dentro do create philos? //
	[] create routine function  in philo_utils.c
		? What each philosopher has to do ? In which order ?
		[x] consider:
			[x] impar and par
			[x] mutex lock
			[x] mutex unlock
		[x] eat
			[x] time_last_meal  init when we starts to eat
			[x] meals_eaten++;
			[] philo_eaten ++ ?;
		[x] sleep
		[x] think /shit
		[x] repeat
		[x] printf
	[x] start_time ? //! (get_my_time)
	[x] while(nrb_philos)
		[x] p_thread_create(table->philo->theread_id, routine, table->philo);
	[x] p_thread_create(..., death_routine)

[]check_is_alive - death_routine)
	[] new routine
	[] mutex lock;
	[] mutex unlock;
	[] call a function to check if the philo eat
	[] call to check is alive;

[] ? - threads_join
	[]while(nbr_philos);
		[]p_thread_join();

[x] free
	[x] philo
		[x] r_fokr;
		[x] l_fork;
		[x] *info;
	[x] distroy mustex forks;
*/

/*
Core concepts:
	[] process vs threads
	[] threads
	[] mutexes
	bonus:
		[] semaphores

[] #define ERROR_MSG;
[] structs:
	[] philo  - principal
		[x] id (number);
		[x] p_thread
		[x] mutex rigth_fork;
		[x] mutex left_fork;
		[x] time_last_meal;
		[x] meals_eaten ?;
		[x] t_info *info;

	[X] info
		[x] start_time;
		[x] nbr_of_philo;
		[x] time_to_die;
		[x] time_to_eat;
		[x] time_to_sleep;
		[x] nbr_of_meals;
		[x] int died ?;
		[x] int all_eaten ;

*/
