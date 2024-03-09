/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:19:46 by yutakagi          #+#    #+#             */
/*   Updated: 2024/03/09 18:12:59 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	// pthread_mutex_lock(&philo->game->death);
	// if(philo->game->is_gameover == true)
	// {
	// 	pthread_mutex_unlock(&philo->game->death);
	// 	return (FAILURE);
	// }
	print_forks(philo);
	pthread_mutex_lock(philo->right_fork);
	// if(philo->game->is_gameover == true)
	// {
	// 	pthread_mutex_unlock(&philo->game->death);
	// 	return (FAILURE);
	// }
	// pthread_mutex_unlock(&philo->game->death);
	print_forks(philo);
	return (SUCCESS);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	get_sleep(t_philo *philo)
{
	print_sleeping(philo);
	time_sleep(philo->game->time_to_sleep);
}
