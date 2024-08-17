/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:25:07 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/17 19:40:27 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	inspect_philos(int nop, t_philo **philos, t_common_data *common)
{
	int		i;
	uint8_t	anyone_died;
	time_t	current_time;

	anyone_died = 0;
	while (!anyone_died)
	{
		i = 0;
		while (i < nop)
		{
			current_time = get_ms() - common->start_time;
			if (last_eat(philos[i]) + common->limit_time < current_time
				|| !isalive(philos[i]))
			{
				p_log(philos[i], DEAD);
				anyone_died = 1;
				break ;
			}
			i++;
		}
	}
}

void	wait_philos(int nop, t_philo **philos, t_common_data *common)
{
	int	i;

	i = 0;
	usleep(500);
	inspect_philos(nop, philos, common);
	while (i < nop)
	{
		pthread_join(philos[i]->thread, NULL);
		free(philos[i++]);
	}
	free(philos);
}
