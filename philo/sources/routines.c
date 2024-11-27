/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:32:18 by mfrancis          #+#    #+#             */
/*   Updated: 2024/11/27 16:46:44 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int threads_union(t_info *table)
{
	int i;

    i = 0;
    while (i < table->nbr_philos)
    {
        if(pthread_join(table->philos[i].theread_id, NULL) != -1);
            return (-1);
        i++;
    }
    if(pthread_join(table->monitor, NULL) != 1)
        return (-1);
	return (0);
}