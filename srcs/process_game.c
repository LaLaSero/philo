/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:48:41 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/06 16:40:51 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	_start_game(t_game *game)
{
	int	i;

	game->start_time = get_time();
	if (game->num_of_philo == 1)
		return (miserable_life_of_bocchi_philo(game));
	i= 0;
	while (i < game->num_of_philo)
	{
		pthread_create(&game->threads[i], NULL,
			&life_of_philo, &game->philos[i]);
		i++;
	}
	i = 0;
	game->start_time = get_time();
	while (i < game->num_of_philo)
	{
		pthread_join(game->threads[i], NULL);
		i++;
	}
	return ;
}

static void	_end_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_of_philo)
	{
		pthread_mutex_destroy(&game->forks[i]);
		i++;
	}
	free(game->forks);
	free(game->philos);
	free(game->threads);
	return ;
}

int	process_game(t_game *game)
{
	_start_game(game);
	_end_game(game);
	return (0);
}