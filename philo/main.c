/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco42 <bvelasco42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:26:58 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/12 00:51:38 by bvelasco42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_common_data	*init_common(int argc, char **argv)
{
	t_common_data	*result;

	if (!verify_args(argc, argv))
		return (NULL);
	result = malloc(sizeof(t_common_data));
	if (!result)
		return (NULL);
	result->nop = ft_atoi(argv[1]);
	if (result->nop < 1)
		return (free(result), NULL);
	result->limit_time = ft_atoi(argv[2]);
	result->eat_time = ft_atoi(argv[3]);
	result->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		result->max_eats = ft_atoi(argv[5]);
	else
		result->max_eats = -1;
	pthread_mutex_init(&result->start_mutex, NULL);
	pthread_mutex_init(&result->log_mutex, NULL);
	pthread_mutex_lock(&result->start_mutex);
	return (result);
}

pthread_mutex_t	*create_forks(int nof)
{
	int				i;
	pthread_mutex_t	*result;

	result = malloc(nof * sizeof(pthread_mutex_t));
	if (!result)
		return (0);
	i = 0;
	while (i < nof)
		pthread_mutex_init(&result[i++], NULL);
	return (result);
}

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

int	main(int argc, char *argv[])
{
	int				i;
	t_philo			**philos;
	t_common_data	*common;
	pthread_mutex_t	*forks;

	i = 0;
	common = init_common(argc, argv);
	if (!common)
		return (0);
	philos = malloc(common->nop * sizeof(void *));
	if (!philos)
		return (free(common), 1);
	forks = create_forks(common->nop);
	while (i < common->nop - 1)
	{
		philos[i] = new_philo(&forks[i], &forks[i + 1], common);
		if (!philos[i])
			return (clean_phill(philos, i), free(common), free(forks), 0);
		i++;
	}
	philos[i] = new_philo(&forks[i], &forks[0], common);
	common->start_time = get_ms();
	pthread_mutex_unlock(&common->start_mutex);
	wait_philos(common->nop, philos, common);
	return (free(common), free(forks), 0);
}
