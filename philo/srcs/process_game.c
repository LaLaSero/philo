/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:48:41 by yutakagi          #+#    #+#             */
/*   Updated: 2024/03/09 17:19:56 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	_miserable_life_of_bocchi_philo(t_game *game)
{
	print_thinking(&game->philos[0]);
	time_sleep(game->time_to_die);
	print_dead(&game->philos[0]);
	return ;
}

static void	_start_game(t_game *game)
{
	int	i;

	game->start_time = get_time();
	if (game->num_of_philo == 1)
		return (_miserable_life_of_bocchi_philo(game));
	i= 0;
	while (i < game->num_of_philo)
	{
		pthread_create(&game->threads[i], NULL,
			&life_of_philo, &game->philos[i]);
		i++;
	}
	i = 0;
	pthread_create(&game->pid_of_monitoring, NULL, &monitor_philo, game);
	pthread_detach(game->pid_of_monitoring);
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
	pthread_mutex_destroy(&game->death);
	pthread_mutex_destroy(&game->eating);
	pthread_mutex_destroy(&game->timing);
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