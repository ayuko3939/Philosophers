/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:00:25 by yohasega          #+#    #+#             */
/*   Updated: 2024/10/06 18:59:35 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	lnum;
	int		sign;

	lnum = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		if (lnum > LONG_MAX / 10 || (lnum == LONG_MAX / 10 && (*str
					- '0') > LONG_MAX % 10))
		{
			if (sign < 0)
				return ((int)LONG_MIN);
			return ((int)LONG_MAX);
		}
		lnum = lnum * 10 + (*str - '0');
		str++;
	}
	return ((int)(lnum * sign));
}

int	error_free(char *msg, t_data *data)
{
	if (data != NULL)
		free_data(data);
	if (msg != NULL)
		error_msg(msg);
	return (EXIT_FAILURE);
}

int	error_msg(char *s)
{
	int	len;

	if (s == NULL)
		return (EXIT_FAILURE);
	len = 0;
	while (s[len] != '\0')
		len++;
	write(2, s, len);
	return (EXIT_FAILURE);
}

void	*free_data(t_data *data)
{
	if (data == NULL)
		return (NULL);
	if (data->forks != NULL)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos != NULL)
	{
		free(data->philos);
		data->philos = NULL;
	}
	return (NULL);
}

int	destroy_all(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->write_lock);
	i = 0;
	while (i < data->philos_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (0);
}
