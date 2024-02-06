/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:48:41 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/06 14:40:48 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_game(t_game *game)
{
	int	i;

	game->start_time = get_time();
	if (game->num_of_philo == 1)
		return (miserable_life_of_bocchi_philo(game));
	// i = 0;
	// while(i < game->num_of_philo)
	// {
	// 	printf("philo %d\n", game->philos[i].id);
	// 	printf("left_fork %p\n", game->philos[i].left_fork);
	// 	printf("right_fork %p\n", game->philos[i].right_fork);
	// 	printf("last_eat %ld\n", game->philos[i].last_eat);
	// 	printf("eat_count %d\n", game->philos[i].eat_count);
	// 	printf("is_dead %d\n", game->philos[i].is_dead);
	// 	i++;
	// }
	printf("\n\n");
	i= 0;
	while (i < game->num_of_philo)
	{
		pthread_create(&game->threads[i], NULL, &life_of_philo, &game->philos[i]);
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

void	end_game(t_game *game)
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