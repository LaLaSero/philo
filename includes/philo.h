/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:14:29 by yutakagi          #+#    #+#             */
/*   Updated: 2024/02/07 15:43:50 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <stdbool.h>

struct	s_game;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_eat;
	int				eat_count;
	pthread_t		thread;
	// pthread_t		pid_of_monitoring;
	struct s_game	*game;
	bool			is_dead;
}				t_philo;

typedef struct s_game
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	long			start_time;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	pthread_mutex_t	eating;
	pthread_mutex_t	timing;
	pthread_t		pid_of_monitoring;
	int				is_gameover;
}				t_game;

int				is_valid_args(int argc, char **argv);

pthread_mutex_t	*init_forks(int num_of_philo);
t_philo			*init_philos(int num_of_philo, t_game *game);
int				init_game(t_game *game , int argc, char **argv);

int				process_game(t_game *game);

void			*life_of_philo(void *philo_dum);
void			miserable_life_of_bocchi_philo(t_game *game);

void			*monitor_philo(void *game_dum);
bool			is_game_clear(t_game *game);

void			print_thinking(t_philo *philo);
void			print_eating(t_philo *philo);
void			print_forks(t_philo *philo);
void			print_sleeping(t_philo *philo);
void			print_dead(t_philo *philo);

void			time_sleep(int milisec);
long			get_time(void);
int				ft_atoi(const char *string);
int				show_usage(void);
int				show_error_message(void);

# ifndef INVALID
	#define  INVALID 0
# endif

# ifndef VALID
	#define  VALID 1
# endif

#ifndef SUCCESS
	#define SUCCESS 0
#endif

#ifndef FAILURE
	#define FAILURE 1
#endif

#endif