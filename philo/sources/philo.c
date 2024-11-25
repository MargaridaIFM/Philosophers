/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:30:56 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/25 23:43:08 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
        [x] bool died ?;
        [x] bool all_eaten ;
        




Create the correct number of philosopher


Create the correct number of threads


Create a routine
    [] What each philosopher has to do ? In which order ?
        [] eat
        [] sleep
        [] think /shit
        [] repeat
[] Initiate the threads with said routine
   
*/

int main(int argc, char *argv[])
{
    t_info table; 
    // t_philo *philos; // apagar
    //pthread_mutex_t *forks; // apagar
    (void)argv;
    
    if (argc != 5 && argc != 6)
    {
        ft_putstr_fd("ERROR: Wrong number of elements\n", 2);
        return (0); // nao podes usar o exit
    }
    table.start_time = ft_my_time();
    printf("time: %u", table.start_time);
    printf("novo tempo: %u\n", ft_my_time()- table.start_time);
    // clean_mem();
    // check_args;
        // check num of philos
    // init_table(&table, argv);
    // init_forks
    // philos = malloc(sizeof(table->philo) * table->nbr_of_philos)); // dentro do create philos
    // create_philos(table);   
    // init_threads
    //
    // 
    return (0);
}

// void init_table(t)

/*
    [] parsing
        [] initialization
            [] struct table
                [] funcao my_time - vai ser usada ao longo do programa;
                    [] start_time with the function get_time;
                    [] e ver p transformar em milisegundos;
        [] guardar na table os arvgs
            [] if argv[1] == 1
                [] morreu
            [] atoi so positivos
*/

// init_table
// [] get_time
// [] args
// [] init mutex forks;

// [] create_philos ? 
//    [] malloc - antes ou depois
//    [] init philos


//    []  inicia threat;
//    []  fork assigment - mutex rigth and left
//          [] create routine function

//