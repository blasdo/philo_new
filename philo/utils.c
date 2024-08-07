/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:48:48 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/07 18:12:02 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_ms(void)
{
	time_t			result;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	result = tv.tv_sec * 1000;
	result += tv.tv_usec / 1000;
	return (result);
}

void	clean_phill(t_philo **philo, int creat)
{
	int	i;

	i = 0;
	while (i < creat)
		free(philo[i++]);
	free(philo);
}
