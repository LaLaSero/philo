/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:32:03 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/05 17:44:14 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void print_eating(t_philo *philo)
{
	printf("%ld %d is eating\n", get_time() - philo->game->start_time, philo->id);
}

void print_sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time() - philo->game->start_time, philo->id);
}

void print_thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time() - philo->game->start_time, philo->id);
}

void print_dead(t_philo *philo)
{
	printf("%ld %d is dead\n", get_time() - philo->game->start_time, philo->id);
}

void print_forks(t_philo *philo)
{
	printf("%ld %d has taken a fork\n", get_time() - philo->game->start_time, philo->id);
}