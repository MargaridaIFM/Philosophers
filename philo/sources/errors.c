/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:53:22 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/27 15:26:10 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void free_all(t_info *table)
// {
//     if(table->philos)
//         free_philos(table);
//     if(table->forks)
//         free_forks(table);
        
// }
// void free_philos(t_info *table)
// {
//     int i;
//     while(i < table->nbr_philos)
//     {
//         table->philos[i].one_fork = NULL;
//         table->philos[i].two_fork = NULL;
//         table->philos[i].table = NULL;
//         free(table->philos[i]);
//         i++;
//     }
// }

// void free_forks(t_info *table)
// {
//     int i;
//     while(i < table->nbr_philos)
//     {
        
//         free(table->forks[i]);
//         i++;
//     }
// }