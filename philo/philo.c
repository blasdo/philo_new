/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco42 <bvelasco42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:59:49 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/16 15:27:28 by bvelasco42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_first_right(t_philo *this)
{
	const t_common_data	*cn = this->common_data;

	if (!isalive(this))
		return ;
	pthread_mutex_lock(this->forks[1]);
	p_log(this, FORK);
	pthread_mutex_lock(this->forks[0]);
	p_log(this, FORK);
	if (get_ms() > this->last_time_eat + cn->start_time + cn->limit_time)
		p_log(this, DEAD);
	p_log(this, EAT);
	pthread_mutex_lock(&(this->philo_mutex));
	this->last_time_eat = get_ms() - this->common_data->start_time;
	pthread_mutex_unlock(&(this->philo_mutex));
	usleep(this->common_data->eat_time * 1000);
	pthread_mutex_unlock(this->forks[0]);
	pthread_mutex_unlock(this->forks[1]);
}

void	eat_first_left(t_philo *this)
{
	const t_common_data	*cn = this->common_data;

	if (!isalive(this))
		return ;
	if (this->forks[0] == this->forks[1])
		return (usleep(this->common_data->limit_time), p_log(this, DEAD));
	pthread_mutex_lock(this->forks[0]);
	p_log(this, FORK);
	pthread_mutex_lock(this->forks[1]);
	p_log(this, FORK);
	if (get_ms() > this->last_time_eat + cn->start_time + cn->limit_time)
		p_log(this, DEAD);
	p_log(this, EAT);
	pthread_mutex_lock(&(this->philo_mutex));
	this->last_time_eat = get_ms() - this->common_data->start_time;
	pthread_mutex_unlock(&(this->philo_mutex));
	usleep(this->common_data->eat_time * 1000);
	pthread_mutex_unlock(this->forks[1]);
	pthread_mutex_unlock(this->forks[0]);
}

void	p_sleep(t_philo *this)
{
	if (!isalive(this))
		return ;
	p_log(this, SLEEP);
	usleep(this->common_data->sleep_time * 1000);
	verify_eat_time(this);
}

void	think(t_philo *this)
{
	int	noe;

	noe = this->common_data->max_eats;
	while (isalive(this) && noe)
	{
		p_log(this, THINK);
		if (this->id % 2 == 0 && this->common_data->nop % 2 == 0)
			eat_first_left(this);
		else
			eat_first_right(this);
		p_sleep(this);
		if (noe > 0)
			noe--;
	}
	pthread_mutex_lock(&this->philo_mutex);
	this->hasfinished = 1;
	pthread_mutex_unlock(&this->philo_mutex);
}
