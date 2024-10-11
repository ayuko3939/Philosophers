/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:20:54 by yohasega          #+#    #+#             */
/*   Updated: 2024/10/09 15:43:25 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	everyone_is_alive(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead == true)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (false);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (true);
}

bool	everyone_is_full(t_data *data)
{
	int	i;

	i = 0;
	if (data->must_eat == -1)
		return (false);
	pthread_mutex_lock(&data->eat_lock);
	while (i < data->philos_num)
	{
		if (data->philos[i].eat_count < data->must_eat)
		{
			pthread_mutex_unlock(&data->eat_lock);
			return (false);
		}
		i++;
	}
	data->finished = true;
	pthread_mutex_unlock(&data->eat_lock);
	return (true);
}

bool	check_anyone_dead(t_data *data, int i)
{
	pthread_mutex_lock(&data->eat_lock);
	if (get_current_time() - data->philos[i].last_eat >= data->time_to_die)
	{
		print_msg(&data->philos[i], DIED, get_current_time());
		pthread_mutex_lock(&data->dead_lock);
		data->dead = true;
		pthread_mutex_unlock(&data->dead_lock);
		pthread_mutex_unlock(&data->eat_lock);
		return (true);
	}
	pthread_mutex_unlock(&data->eat_lock);
	return (false);
}

bool	check_finished(t_data *data)
{
	pthread_mutex_lock(&data->eat_lock);
	if (data->finished)
	{
		pthread_mutex_unlock(&data->eat_lock);
		return (true);
	}
	pthread_mutex_unlock(&data->eat_lock);
	return (false);
}
