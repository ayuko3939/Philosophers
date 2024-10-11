/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:27:17 by yohasega          #+#    #+#             */
/*   Updated: 2024/10/06 22:21:51 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		if (i == data->philos_num - 1)
			data->philos[i].right_fork = &data->forks[0];
		else
			data->philos[i].right_fork = &data->forks[i + 1];
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (error_msg("pthread_mutex_init\n"));
		}
		i++;
	}
	return (0);
}

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->eat_lock, NULL) != 0)
		return (error_msg("pthread_mutex_init error\n"));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->eat_lock);
		return (error_msg("pthread_mutex_init error\n"));
	}
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->eat_lock);
		pthread_mutex_destroy(&data->write_lock);
		return (error_msg("pthread_mutex_init error\n"));
	}
	return (0);
}

static int	allocate_data(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philos_num);
	if (data->philos == NULL)
		return (error_msg("malloc error\n"));
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philos_num);
	if (data->forks == NULL)
	{
		free(data->philos);
		return (error_msg("malloc error\n"));
	}
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->philos_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	data->finished = false;
	data->dead = false;
	data->start_time = get_current_time() + (data->philos_num * 20);
	if (allocate_data(data))
		return (1);
	if (init_mutexes(data))
		return (error_free("NULL", data));
	if (init_philos(data))
	{
		pthread_mutex_destroy(&data->dead_lock);
		pthread_mutex_destroy(&data->eat_lock);
		pthread_mutex_destroy(&data->write_lock);
		return (error_free("NULL", data));
	}
	return (0);
}
