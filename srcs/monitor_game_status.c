/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_game_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:48:42 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/06 17:46:30 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	is_game_clear(t_game *game)
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
		pthread_mutex_lock(&game->death_flag);
		if (is_game_clear(game) == true)
		{
			pthread_mutex_unlock(&game->death_flag);
			return (NULL);
		}
		if (get_time() - game->philos[i].last_eat > game->time_to_die
			&& game->philos[i].last_eat != -1)
		{
			game->philos[i].is_dead = true;
			print_dead(&game->philos[i]);
			pthread_mutex_unlock(&game->death_flag);
			exit(FAILURE);
		}
		pthread_mutex_unlock(&game->death_flag);
		i = (i + 1) % game->num_of_philo;
	}
	return (NULL);
}
