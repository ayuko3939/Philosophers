/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:44:00 by yohasega          #+#    #+#             */
/*   Updated: 2024/10/11 19:33:08 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// ======================= enum =======================

typedef enum e_status
{
	GOT_FORK = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	DIED = 4
}						t_status;

// ==================== structures ====================

typedef struct s_philo	t_philo;

typedef struct s_data
{
	t_philo				*philos;
	int					philos_num;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					must_eat;
	bool				finished;
	time_t				start_time;
	bool				dead;
	pthread_mutex_t		*forks;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
}						t_data;

typedef struct s_philo
{
	pthread_t			philo;
	int					id;
	time_t				last_eat;
	int					eat_count;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	t_data				*data;
}						t_philo;

// ==================== functions =====================

int						validate(int ac, char **av);

int						init_data(t_data *data, int ac, char **av);

void					monitor(t_data *data);

void					philosophers(t_data *data);

void					lonely_philo(t_philo *philo);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					eating(t_philo *philo);
void					*routine(void *arg);

bool					everyone_is_alive(t_data *data);
bool					everyone_is_full(t_data *data);
bool					check_anyone_dead(t_data *data, int i);
bool					check_finished(t_data *data);

void					print_msg(t_philo *philo, t_status status,
							int current_time);
void					standby(t_philo *philo);
void					get_forks(t_philo *philo);
void					return_foks(t_philo *philo);

void					start_delay(time_t start_time);
time_t					get_current_time(void);
int						my_usleep(size_t milliseconds);

int						ft_atoi(const char *str);
int						error_free(char *msg, t_data *data);
int						error_msg(char *s);
void					*free_data(t_data *data);
int						destroy_all(t_data *data);

#endif