/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:01:34 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/12 10:41:30 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	idx;

	idx = 0;
	while (s[idx])
	{
		write(fd, &s[idx], 1);
		idx++;
	}
}

unsigned int	ft_my_time(void)
{
	unsigned int	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	clean_mem(t_info *table)
{
	table->start_time = 0;
	table->nbr_philos = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->time_to_think = 0;
	table->nbr_of_meals = 0;
	table->extermination = 0;
	table->philos_eaten = 0;
	table->philos = NULL;
	table->forks = NULL;
	table->monitor = 0;
}

unsigned int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	unsigned int	neg;
	unsigned int	final_nr;

	neg = 1;
	final_nr = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		final_nr = (final_nr * 10) + (nptr[i] - '0');
		i++;
	}
	return (final_nr * neg);
}

int	check_args(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
			{
				ft_putstr_fd("ERROR: Invalid format!\n", 2);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
