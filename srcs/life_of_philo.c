/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:12:08 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/07 18:15:01 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	_mark_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->timing);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->game->timing);
}

static void	_inclease_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->eating);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->game->eating);
}

static bool	_check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->death);
	if (philo->is_dead == true
		|| philo->game->is_gameover== true)
	{
		pthread_mutex_unlock(&philo->game->death);
		return (true);
	}
	pthread_mutex_unlock(&philo->game->death);
	return (false);
}

static bool _should_continue(t_philo *philo)
{
	if (_check_dead(philo) == true
		|| philo->eat_count == philo->game->num_of_must_eat)
		return (false);
	return (true);
}

void	*life_of_philo(void *philo_dum)
{
	t_philo	*philo;

	philo = (t_philo *)philo_dum;
	philo->last_eat = get_time();
	if (philo->id % 2 == 0)
		time_sleep(1);
	while (1)
	{
		if (_should_continue(philo) == false)
			return (NULL);
		print_thinking(philo);
		if (take_forks(philo) == FAILURE)
			return (NULL);
		print_eating(philo);
		_mark_last_eat(philo);
		time_sleep(philo->game->time_to_eat);
		_inclease_eat_count(philo);
		put_down_forks(philo);
		get_sleep(philo);
	}
	return (NULL);
}
