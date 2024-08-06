/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument-control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:26:23 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/06 17:26:57 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	res;

	sign = 0;
	res = 0;
	while (isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = 1;
		nptr++;
	}
	while (isdigit(*nptr))
	{
		if (sign == 0)
			res = (res * 10) + (*(nptr++) - '0');
		else
			res = (res * 10) - (*(nptr++) - '0');
	}
	return (res);
}

uint8_t	verify_args(int argc, char **argv)
{
	int	i;

	if (argc < 4 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!ft_isnumber(argv[i++]))
			return (0);
	}
	return (1);
}