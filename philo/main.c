/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:26:58 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/17 19:41:19 by bvelasco         ###   ########.fr       */
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
	if (pthread_mutex_init(&result->start_mutex, NULL))
		return (free(result), NULL);
	if (pthread_mutex_init(&result->log_mutex, NULL))
		return (free(result), NULL);
	if (pthread_mutex_lock(&result->start_mutex))
		return (free(result), NULL);
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

t_philo	**init_philos(t_common_data *common, pthread_mutex_t *forks)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = malloc(common->nop * sizeof(void *));
	if (!philos)
		return (0);
	while (i < common->nop - 1)
	{
		philos[i] = new_philo(&forks[i], &forks[i + 1], common);
		if (!philos[i])
			return (clean_phill(philos, i), NULL);
		i++;
	}
	philos[i] = new_philo(&forks[i], &forks[0], common);
	return (philos);
}

int	main(int argc, char *argv[])
{
	t_philo			**philos;
	t_common_data	*common;
	pthread_mutex_t	*forks;

	common = init_common(argc, argv);
	if (!common)
		return (1);
	forks = create_forks(common->nop);
	if (!forks)
		return (free(common), 1);
	philos = init_philos(common, forks);
	if (!philos)
		return (free(common), free(forks), 1);
	common->start_time = get_ms();
	pthread_mutex_unlock(&common->start_mutex);
	wait_philos(common->nop, philos, common);
	return (free(common), free(forks), 0);
}
