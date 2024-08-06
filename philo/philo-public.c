/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-public.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:31:57 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/06 12:48:26 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	last_eat(t_philo *this)
{
	time_t	result;

	pthread_mutex_lock(&this->philo_mutex);
	result = this->last_time_eat;
	pthread_mutex_unlock(&this->philo_mutex);
	return (result);
}

void	hemlock(t_philo *this)
{
	pthread_mutex_lock(&this->philo_mutex);
	this->isalive = 0;
	pthread_mutex_unlock(&this->philo_mutex);
}

void	p_log(t_philo *this, t_action act)
{
	const char		*actions[5] = {"is thinking", "has taken a fork",
		"is eating", "is sleeping", "died"};
	static uint8_t	canwrite = 1;

	if (!isalive(this) || p_hasfinished(this))
		return ;
	pthread_mutex_lock(&this->common_data->log_mutex);
	if (canwrite)
	{
		printf("%li %i %s\n", get_ms() - this->common_data->start_time,
			this->id, actions[act]);
		if (act == DEAD)
		{
			canwrite = 0;
			hemlock(this);
		}
	}
	else
		hemlock(this);
	pthread_mutex_unlock(&this->common_data->log_mutex);
}
