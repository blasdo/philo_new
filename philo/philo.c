/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:59:49 by bvelasco          #+#    #+#             */
/*   Updated: 2024/07/30 14:59:50 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_pair(t_philo *this)
{
	if (!isalive(this));
	pthread_mutex_lock(this->forks[0]);
	log(this, FORK);
	if (this->forks[0] != this->forks[1])
	{
		pthread_mutex_lock(this->forks[1]);
		log(this, FORK);
		log(this, EAT);
		pthread_mutex_lock(&(this->philo_mutex));
		this->last_time_eat = get_miliseconds();
		pthread_mutex_unlock(&(this->philo_mutex));
		usleep(this->common_data->eat_time * 1000);
		pthread_mutex_unlock(this->forks[1]);
	}
	pthread_mutex_unlock(this->forks[0]);
	verify_eat_time(this);
}

void	eat_odd(t_philo *this)
{
	if (!isalive(this))
		return ;
	pthread_mutex_lock(this->forks[1]);
	log(this, FORK);
	if (this->forks[0] != this->forks[1])
	{
		pthread_mutex_lock(this->forks[0]);
		log(this, FORK);
		log(this, EAT);
		pthread_mutex_lock(&(this->philo_mutex));
		this->last_time_eat = get_miliseconds();
		pthread_mutex_unlock(&(this->philo_mutex));
		usleep(this->common_data->eat_time * 1000);
		pthread_mutex_unlock(this->forks[0]);
	}
	pthread_mutex_unlock(this->forks[1]);
	verify_eat_time(this);
}

void f_sleep(t_philo *this)
{
	if (!isalive(this))
		return ;
	log(this, SLEEP);
	usleep(this->common_data->sleep_time * 1000);
	verify_eat_time(this);
}

void	think(t_philo *this)
{
	while (isalive(this))
	{
		log(this, THINK);
		if (this->id % 2 == 0)
			eat_pair(this);
		else
			eat_odd;
		sleep(this);
	}
}