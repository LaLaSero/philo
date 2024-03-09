/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:01:17 by yutakagi          #+#    #+#             */
/*   Updated: 2024/03/09 18:47:57 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *string)
{
	int		flag;
	long	result;

	while (*string == ' ' || *string == '\t' || *string == '\n'
		|| *string == '\v' || *string == '\f' || *string == '\r')
		string++;
	flag = 1;
	if (*string == '-' || *string == '+')
	{
		if (*string == '-')
			flag *= -1;
		string++;
	}
	result = 0;
	while (*string >= '0' && *string <= '9')
	{
		if (result * flag > LONG_MAX / 10
			|| (result * flag == LONG_MAX / 10 && *string - '0' > 7))
			return ((int)LONG_MAX);
		if (result * flag < LONG_MIN / 10
			|| (result * flag == LONG_MIN / 10 && *string - '0' > 8))
			return ((int)LONG_MIN);
		result = result * 10 + (*string++ - '0');
	}
	return (result * flag);
}

// void	time_sleep(int milisec)
// {
// 	usleep(milisec * 1000);
// }

void	time_sleep(int time)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time)
		usleep(150);
	return ;
}

int	show_usage()
{
	printf("Usage: ./philo \
	[number_of_philosophers]\
	[time_to_die]\
	[time_to_eat]\
	[time_to_sleep]\
	[number_of_time_each_philosophers_must_eat]\n\
	every parameter should be a positive integer smaller than INT_MAX\n");
	return(FAILURE);
}

int	show_error_message()
{
	printf("Error: failed to initialize the game\n");
	return (FAILURE);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}