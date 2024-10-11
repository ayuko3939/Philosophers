/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:28:27 by yohasega          #+#    #+#             */
/*   Updated: 2024/10/06 23:02:08 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_data *data)
{
	int	i;

	if (data->must_eat == 0)
		return ;
	start_delay(data->start_time);
	while (1)
	{
		i = 0;
		while (i < data->philos_num)
		{
			if (check_anyone_dead(data, i))
				return ;
			i++;
		}
		if (everyone_is_full(data))
			return ;
		usleep(300);
	}
}
