/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:10:28 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/05 17:53:58 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char **argv)
{
	t_game game;

	if (is_valid_args(argc, argv) == INVALID
		|| init_game(&game, argc, argv) == FAILURE)
		return (show_usage());
	start_game(&game);
	end_game(&game);
	return (0);
}