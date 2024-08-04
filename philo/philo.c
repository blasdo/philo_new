/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:59:49 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/04 19:54:26 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_pair(t_philo *this)
{
	const t_common_data	*common = this->common_data;

	if (!isalive(this))
		return ;
	pthread_mutex_lock(this->forks[0]);
	p_log(this, FORK);
	if (this->forks[0] != this->forks[1])
	{
		pthread_mutex_lock(this->forks[1]);
		p_log(this, FORK);
		if (get_milliseconds() > this->last_time_eat + common->start_time + common->limit_time)
			p_log(this, DEAD);
		p_log(this, EAT);
		pthread_mutex_lock(&(this->philo_mutex));
		this->last_time_eat = get_milliseconds() - this->common_data->start_time;
		pthread_mutex_unlock(&(this->philo_mutex));
		usleep(this->common_data->eat_time * 1000);
		pthread_mutex_unlock(this->forks[1]);
	}
	else
	{
		usleep(common->limit_time * 1000);
		p_log(this, DEAD);
	}
	pthread_mutex_unlock(this->forks[0]);
}

void	eat_odd(t_philo *this)
{
	const t_common_data	*common = this->common_data;

	if (!isalive(this))
		return ;
	pthread_mutex_lock(this->forks[1]);
	p_log(this, FORK);
	if (this->forks[0] != this->forks[1])
	{
		pthread_mutex_lock(this->forks[0]);
		p_log(this, FORK);
		if (get_milliseconds() > this->last_time_eat + common->start_time + common->limit_time)
			p_log(this, DEAD);
		p_log(this, EAT);
		pthread_mutex_lock(&(this->philo_mutex));
		this->last_time_eat = get_milliseconds() - this->common_data->start_time;
		pthread_mutex_unlock(&(this->philo_mutex));
		usleep(this->common_data->eat_time * 1000);
		pthread_mutex_unlock(this->forks[0]);
	}
	else
	{
		usleep(common->limit_time * 1000);
		p_log(this, DEAD);
	}
	pthread_mutex_unlock(this->forks[1]);
}

void p_sleep(t_philo *this)
{
	if (!isalive(this))
		return ;
	p_log(this, SLEEP);
	usleep(this->common_data->sleep_time * 1000);
	verify_eat_time(this);
}

void	think(t_philo *this)
{
	while (isalive(this))
	{
		p_log(this, THINK);
		if (this->id % 2 == 0)
			eat_pair(this);
		else
			eat_odd(this);
		p_sleep(this);
	}
}