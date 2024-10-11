/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:32:13 by yohasega          #+#    #+#             */
/*   Updated: 2024/10/09 15:43:30 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, GOT_FORK, get_current_time());
	pthread_mutex_unlock(philo->left_fork);
	my_usleep(philo->data->time_to_die);
}

void	thinking(t_philo *philo)
{
	time_t	left_time;
	time_t	time_to_think;

	left_time = philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep;
	time_to_think = (philo->data->time_to_die - (get_current_time()
				- philo->last_eat) - philo->data->time_to_eat) / 2;
	if (time_to_think > left_time)
		time_to_think = left_time;
	if (time_to_think <= 0)
		time_to_think = 1;
	print_msg(philo, THINKING, get_current_time());
	my_usleep(time_to_think);
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, SLEEPING, get_current_time());
	my_usleep(philo->data->time_to_sleep);
}

void	eating(t_philo *philo)
{
	get_forks(philo);
	print_msg(philo, EATING, get_current_time());
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->eat_count++;
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(&philo->data->eat_lock);
	my_usleep(philo->data->time_to_eat);
	return_foks(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->must_eat == 0)
		return (NULL);
	start_delay(philo->data->start_time);
	if (philo->data->philos_num == 1)
	{
		lonely_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		standby(philo);
	while (everyone_is_alive(philo->data))
	{
		if (check_finished(philo->data))
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
