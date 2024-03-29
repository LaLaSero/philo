/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:47:05 by yutakagi          #+#    #+#             */
/*   Updated: 2024/03/09 18:57:28 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_philo	*_init_philos(int num_of_philo, t_game *game)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * num_of_philo);
	if (!philos)
		return (NULL);
	while (i < num_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &game->forks[i];
		philos[i].right_fork = &game->forks[(i + 1) % num_of_philo];
		philos[i].last_eat = -1;
		philos[i].eat_count = 0;
		philos[i].game = game;
		philos[i].is_dead = false;
		i++;
	}
	return (philos);
}

static pthread_mutex_t	*_init_forks(int num_of_philo)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_of_philo);
	if (!forks)
		return (NULL);
	while (i < num_of_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

static void	_init_monitoring_mutex(t_game *game)
{
	pthread_mutex_init(&game->death, NULL);
	pthread_mutex_init(&game->eating, NULL);
	pthread_mutex_init(&game->timing, NULL);
	return ;
}

int	init_game(t_game *game , int argc, char **argv)
{
	game->is_gameover = false;
	game->num_of_philo = ft_atoi(argv[1]);
	game->time_to_die = ft_atoi(argv[2]);
	game->time_to_eat = ft_atoi(argv[3]);
	game->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		game->num_of_must_eat = ft_atoi(argv[5]);
	else
		game->num_of_must_eat = -1;
	game->start_time = 0;
	_init_monitoring_mutex(game);
	game->threads = malloc(sizeof(pthread_t) * game->num_of_philo);
	game->forks = _init_forks(game->num_of_philo);
	game->philos = _init_philos(game->num_of_philo, game);
	if (!game->threads || !game->philos || !game->forks)
	{
		free(game->threads);
		free(game->philos);
		free(game->forks);
		return (FAILURE);
	}
	return (SUCCESS);
}
