/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-constuctor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:57:09 by bvelasco          #+#    #+#             */
/*   Updated: 2024/07/31 17:39:15 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(pthread_mutex_t *fork_left, pthread_mutex_t *fork_right
	, t_common_data *data)
{
	t_philo			*result;
	static uint32_t	id = 1;
	
	result = malloc(sizeof(data));
	result->id = id;
	result->forks[0] = fork_left;
	result->forks[1] = fork_right;
	result->isalive = 1;
	pthread_mutex_init(&result->philo_mutex, NULL);
	result->common_data = data;
	pthread_create(&result->thread, NULL, start_philo, result);
	return (result);
}

void	*start_philo(void *this)
{
	t_philo	*phil;

	phil = this;
	pthread_mutex_lock(&phil->common_data->start_mutex);
	pthread_mutex_unlock(&phil->common_data->start_mutex);
	phil->last_time_eat = phil->common_data->start_time;
	think(phil);
	return (NULL);
}