/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_game_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:48:42 by yutakagi          #+#    #+#             */
/*   Updated: 2024/03/09 17:25:59 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	_report_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->death);
	philo->is_dead = true;
	philo->game->is_gameover = true;
	pthread_mutex_unlock(&philo->game->death);
	print_dead(philo);
}

static bool	_is_him_dead(t_game *game, int i)
{
	pthread_mutex_lock(&game->timing);
	if (get_time() - game->philos[i].last_eat > game->time_to_die
			&& game->philos[i].last_eat != -1
			&& (game->philos[i].eat_count < game->num_of_must_eat
				|| game->num_of_must_eat == -1))
	{
		pthread_mutex_unlock(&game->timing);
		return (true);
	}
	pthread_mutex_unlock(&game->timing);
	return (false);
}

static bool	_is_game_clear(t_game *game)
{
	int	i;

	if (game->num_of_must_eat == -1)
		return (false);
	i = 0;
	while (i < game->num_of_philo)
	{
		if (game->philos[i].eat_count < game->num_of_must_eat)
			return (false);
		i++;
	}
	return (true);
}

void	*monitor_philo(void *game_dum)
{
	int		i;
	t_game	*game;

	game = (t_game *)game_dum;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&game->eating);
		pthread_mutex_lock(&game->death);
		if (_is_game_clear(game) == true)
		{
			pthread_mutex_unlock(&game->eating);
			pthread_mutex_unlock(&game->death);
			return (NULL);
		}
		if (_is_him_dead(game, i) == true)
		{
			pthread_mutex_unlock(&game->eating);
			pthread_mutex_unlock(&game->death);
			_report_death(&game->philos[i]);
			return (NULL);
		}
		pthread_mutex_unlock(&game->eating);
		pthread_mutex_unlock(&game->death);
		i = (i + 1) % game->num_of_philo;
	}
	return (NULL);
}
