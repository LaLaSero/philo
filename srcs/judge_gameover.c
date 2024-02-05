/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_gameover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:48:42 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/05 21:28:09 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool is_game_clear(t_game *game)
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