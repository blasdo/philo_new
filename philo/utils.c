#include "philo.h"

uint8_t	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
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

time_t	get_milliseconds(void)
{
	time_t			result;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	result = tv.tv_sec * 1000;
	result += tv.tv_usec / 1000;
	return (result);
}