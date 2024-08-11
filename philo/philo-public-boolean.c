/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-public-boolean.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco42 <bvelasco42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:07:51 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/12 00:25:02 by bvelasco42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint8_t	p_hasfinished(t_philo *this)
{
	int	result;

	pthread_mutex_lock(&this->philo_mutex);
	result = this->hasfinished;
	pthread_mutex_unlock(&this->philo_mutex);
	return (result);
}

uint8_t	isalive(t_philo *this)
{
	uint8_t	result;

	pthread_mutex_lock(&this->philo_mutex);
	result = this->isalive;
	pthread_mutex_unlock(&this->philo_mutex);
	return (result);
}

uint8_t	verify_eat_time(t_philo *this)
{
	uint8_t	result;

	result = 0;
	pthread_mutex_lock(&this->philo_mutex);
	if (get_ms()
		> this->last_time_eat + this->common_data->limit_time)
		result = 1;
	pthread_mutex_unlock(&this->philo_mutex);
	return (result);
}
