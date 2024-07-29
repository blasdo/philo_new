#include <philo.h>

time_t	get_milliseconds(void)
{
	time_t			result;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	result = tv.tv_sec * 1000;
	result += tv.tv_usec / 1000;
	return (result);
}