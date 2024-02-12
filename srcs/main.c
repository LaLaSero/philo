/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:10:28 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/07 17:25:55 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char **argv)
{
	t_game	game;

	if (is_valid_args(argc, argv) == INVALID)
		return (show_usage());
	if (init_game(&game, argc, argv) == FAILURE)
		return (show_error_message());
	return (process_game(&game));
}

// __attribute__((destructor))
// static void destructor(){
// 	system("leaks -q philo");
// }
