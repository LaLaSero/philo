/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:19:37 by yutakagi          #+#    #+#             */
/*   Updated: 2024/03/09 18:57:16 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	_is_valid_param(const char *string)
{
	long	result;

	while (*string == ' ' || *string == '\t' || *string == '\n'
		|| *string == '\v' || *string == '\f' || *string == '\r')
		string++;
	if (*string == '-')
		return (INVALID);
	if (*string == '+')
		string++;
	result = 0;
	while (*string >= '0' && *string <= '9')
	{
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10 && *string - '0' > 7))
			return (INVALID);
		result = result * 10 + (*string++ - '0');
	}
	if (*string == '\0' && result > 0)
		return (VALID);
	return (INVALID);
}

int	is_valid_args(int argc, char **argv)
{
	int	i;

	if (!(argc == 5 || argc == 6))
		return (INVALID);
	i = 1;
	while (i < argc)
	{
		if(_is_valid_param(argv[i]) == INVALID)
			return (INVALID);
		i++;
	}
	return (VALID);
}