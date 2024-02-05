/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:12:08 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/05 21:39:45 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	get_sleep(t_philo *philo);

void *monitor_philo(void *game_dum)
{
	int	i;
	t_game *game;

	game = (t_game *)game_dum;
	i = 0;
	while (1)
	{
		if (is_game_clear(game) == true)
			return (NULL);
		if (get_time() - game->philos[i].last_eat > game->time_to_die)
		{
			print_dead(&game->philos[i]);
			exit(FAILURE);
		}
		i = (i + 1) % game->num_of_philo;
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_forks(philo);
	pthread_mutex_lock(philo->right_fork);
	print_forks(philo);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	get_sleep(philo);
}

void	get_sleep(t_philo *philo)
{
	print_sleeping(philo);
	time_sleep(philo->game->time_to_sleep);
}

void	*life_of_philo(void *philo_dum)
{
	t_philo	*philo;

	philo = (t_philo *)philo_dum;
	pthread_create(&philo->pid_of_monitoring, NULL, &monitor_philo, philo->game);
	pthread_detach(philo->pid_of_monitoring);
	philo->last_eat = get_time();
	while (is_game_clear(philo->game) == false)
	{
		print_thinking(philo);
		take_forks(philo);
		print_eating(philo);
		philo->eat_count++;
		philo->last_eat = get_time();
		time_sleep(philo->game->time_to_eat);
		put_down_forks(philo);
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