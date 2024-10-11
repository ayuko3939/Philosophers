/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:22:45 by yohasega          #+#    #+#             */
/*   Updated: 2024/10/07 13:33:02 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, t_status status, int current_time)
{
	int	timestamp;

	timestamp = current_time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_lock);
	if (everyone_is_alive(philo->data))
	{
		if (status == DIED)
			printf("%d %d died\n", timestamp, philo->id);
		else if (status == EATING)
			printf("%d %d is eating\n", timestamp, philo->id);
		else if (status == SLEEPING)
			printf("%d %d is sleeping\n", timestamp, philo->id);
		else if (status == THINKING)
			printf("%d %d is thinking\n", timestamp, philo->id);
		else if (status == GOT_FORK)
			printf("%d %d has taken a fork\n", timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	standby(t_philo *philo)
{
	time_t	left_time;
	time_t	time_to_standby;

	left_time = philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep;
	time_to_standby = (philo->data->time_to_die - philo->data->time_to_eat) / 2;
	if (time_to_standby > left_time)
		time_to_standby = left_time;
	if (time_to_standby <= 0)
		time_to_standby = 1;
	my_usleep(time_to_standby);
}

void	get_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, GOT_FORK, get_current_time());
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, GOT_FORK, get_current_time());
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, GOT_FORK, get_current_time());
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, GOT_FORK, get_current_time());
	}
}

void	return_foks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
