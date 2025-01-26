/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrancis <mfrancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:01:34 by mfrancis          #+#    #+#             */
/*   Updated: 2025/01/26 17:55:24 by mfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Writes a string to the specified file descriptor.
 *
 * @param s Pointer to the string to be written.
 * @param fd File descriptor where the string will be written.
 */
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

/**
 * @brief Calculate the current time in milliseconds using `gettimeofday`
 * function.

 *
 * @return The current time in milliseconds.
 */
unsigned int	ft_my_time(void)
{
	unsigned int	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
/**
 * @brief Converts a string to an unsigned integer.

 *
 * @param nptr Pointer to the string to be converted.
 * @return The converted unsigned integer.
 */

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

/**
 * @brief Validates the arguments provided to the program.
 *
 * Checks if each argument contains only numeric characters.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Array of argument strings.
 * @return 0 if all arguments are valid, -1 otherwise.
 */

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
