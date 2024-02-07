/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:12:08 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/07 17:07:00 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	get_sleep(t_philo *philo);

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if(philo->game->is_gameover == true)
		return (FAILURE);
	print_forks(philo);
	pthread_mutex_lock(philo->right_fork);
	if(philo->game->is_gameover == true)
		return (FAILURE);
	print_forks(philo);
	return (SUCCESS);
}

static void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	get_sleep(t_philo *philo)
{
	print_sleeping(philo);
	time_sleep(philo->game->time_to_sleep);
}

bool check_dead(t_philo *philo)
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



void inclease_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->eating);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->game->eating);
}

void mark_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->timing);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->game->timing);
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
		if (philo->eat_count == philo->game->num_of_must_eat)
			return (NULL);
		if (check_dead(philo) == true)
			return (NULL);
		print_thinking(philo);
		if (take_forks(philo) == FAILURE)
			return (NULL);
		print_eating(philo);
		mark_last_eat(philo);
		time_sleep(philo->game->time_to_eat);
		inclease_eat_count(philo);
		put_down_forks(philo);
		if (philo->game->is_gameover == true)
			return (NULL);
		get_sleep(philo);
	}
	return (NULL);
}

void	miserable_life_of_bocchi_philo(t_game *game)
{
	print_thinking(&game->philos[0]);
	time_sleep(game->time_to_die);
	print_dead(&game->philos[0]);
	return ;
}