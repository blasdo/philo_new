/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument-control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:26:23 by bvelasco          #+#    #+#             */
/*   Updated: 2024/08/07 17:08:29 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(int c)
{
	unsigned char	c_c;

	c_c = (unsigned char) c;
	if (c_c == ' ' || c_c == '\t' || c_c == '\n' || c_c == '\v' || \
	c_c == '\f' || c_c == '\r')
		return (1);
	return (0);
}

uint8_t	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	res;

	sign = 0;
	res = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = 1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
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
