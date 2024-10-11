/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:18:32 by yohasega          #+#    #+#             */
/*   Updated: 2024/10/06 18:52:28 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check number or not, except for space and one '-' or '+'
static int	is_number(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	validate(int ac, char **av)
{
	int	err_flag;

	err_flag = 0;
	if (ac != 5 && ac != 6)
		err_flag = error_msg("Invalid argument\n");
	else
	{
		if (!is_number(av[1]) || ft_atoi(av[1]) <= 0)
			err_flag = error_msg("Invalid philosophers number\n");
		if (!is_number(av[2]) || ft_atoi(av[2]) < 0)
			err_flag = error_msg("Invalid time to die\n");
		if (!is_number(av[3]) || ft_atoi(av[3]) < 0)
			err_flag = error_msg("Invalid time to eat\n");
		if (!is_number(av[4]) || ft_atoi(av[4]) < 0)
			err_flag = error_msg("Invalid time to sleep\n");
		if (ac == 6 && (!is_number(av[5]) || ft_atoi(av[5]) < 0))
			err_flag = error_msg("Invalid number of times to eat\n");
	}
	if (err_flag)
		return (0);
	return (1);
}
