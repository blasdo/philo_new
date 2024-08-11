/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:01:55 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/11 13:15:43 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdint.h>

/*
* Common data
* eat_time: time it takes for a philo to eat
* sleep_time: time it takes for a philo to sleep
* limit_time: if he don't eat before this time of previous eat the philo dead
* log_mutex: common mutex to acess stdout with the internal funct log
* start_mutex: if is locked the main thread is still creating philos.
*/

typedef struct s_common_data
{
	int				nop;
	int				max_eats;
	time_t			eat_time;
	time_t			sleep_time;
	time_t			limit_time;
	time_t			start_time;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	start_mutex;
}				t_common_data;

/*
* Philo class
* id: the philo identifier
* isalive: this philo is alive?
* forks: pointer to his forks
* philo_mutex: his mutex, if is locked anyone can't write
* last_time_eat: last time that the philo was eat.
* common_data: struct of common data
*/

typedef enum e_action
{
	THINK,
	FORK,
	EAT,
	SLEEP,
	DEAD
}			t_action;

typedef struct s_philo
{
	uint32_t		id;
	uint8_t			isalive;
	uint8_t			hasfinished;
	time_t			last_time_eat;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	philo_mutex;
	pthread_t		thread;
	t_common_data	*common_data;
}				t_philo;

void	eat(t_philo *this);
void	p_sleep(t_philo *this);
void	think(t_philo *this);
void	*start_philo(void *philo);
// public
time_t	last_eat(t_philo *this);
uint8_t	isalive(t_philo *this);
uint8_t	p_hasfinished(t_philo *this);
void	p_log(t_philo *phil, t_action act);
t_philo	*new_philo(pthread_mutex_t *fork_left, pthread_mutex_t *fork_right,
			t_common_data *data);
uint8_t	verify_eat_time(t_philo *phil);
//utils
void	clean_phill(t_philo **philo, int creat);
uint8_t	verify_args(int argc, char **argv);
int		ft_atoi(const char *nptr);
time_t	get_ms(void);

#endif