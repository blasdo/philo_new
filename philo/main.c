/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:26:58 by bvelasco          #+#    #+#             */
/*   Updated: 2024/07/31 16:36:51y bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_common_data	*init_common(int argc, char **argv)
{
	t_common_data	*result;

	result = malloc(sizeof(t_common_data));
	if (!result)
		return (NULL);
	result->limit_time = ft_atoi(argv[2]);
	result->eat_time = ft_atoi(argv[3]);
	result->sleep_time = ft_atoi(argv[4]);
	pthread_mutex_init(&result->start_mutex, NULL);
	pthread_mutex_init(&result->log_mutex, NULL);
	pthread_mutex_lock(&result->start_mutex);
	return (result);
}

pthread_mutex_t	*create_forks(int nof)
{
	int	i;
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

	i = 0;
	anyone_died = 0;
	while (!anyone_died)
	{
		while (i < nop)
		{
			current_time = get_milliseconds() - common->start_time;
			if (last_eat(philos[i]) + common->limit_time < current_time)
			{
				p_log(philos[i], DEAD);
				anyone_died = 1;
				break;
			}
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
	int				number_of_philos;
	int				i;
	t_philo			**philos;
	t_common_data	*common;
	pthread_mutex_t	*forks;

	i = 0;
	if (!verify_args(argc, argv))
		return (printf("Invalid arguments\n"), 0);
	number_of_philos = ft_atoi(argv[1]);
	if (number_of_philos <= 0)
		return (printf("Invalid arguments\n"), 0);
	philos = malloc(number_of_philos * sizeof(void *));
	forks = create_forks(number_of_philos);
	if (number_of_philos < 1)
		return (0);
	common = init_common(argc, argv);
	if (!common)
		return (printf("Memory error\n"), 0);
	while (i < number_of_philos - 1)
	{
		philos[i] = new_philo(&forks[i], &forks[i + 1], common);
		i++;
	}
	philos[i] = new_philo(&forks[i], &forks[0], common);
	common->start_time = get_milliseconds();
	pthread_mutex_unlock(&common->start_mutex);
	wait_philos(number_of_philos, philos, common);
	return (free(common), free(forks), 0);
}
