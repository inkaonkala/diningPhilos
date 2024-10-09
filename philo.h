/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:43:44 by iniska            #+#    #+#             */
/*   Updated: 2024/10/09 10:09:56 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO
# define PHILO

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_lockenum
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	JOIN,
	DETACH,
}	t_lockenum;

typedef pthread_mutex_t t_mutex;
typedef	struct s_cave	t_cave;

typedef struct s_fork
{
	t_mutex	fork;
	int		id_fork;
} t_fork;

typedef struct s_philo
{
	int				id_nmb;
	int				meals_eatn;
	pthread_mutex_t	time_lock;
	long			last_food_time;

	t_fork	*first_fork;
	t_fork	*second_fork;

	bool	full;
	bool	dead;
	bool	is_ready;

	pthread_t	thread_id;
	t_cave		*cave;

} t_philo;

struct s_cave
{
	t_fork			*forks;
	t_philo			*philos;

	int				full_philos;

	t_mutex			start_lock;
	pthread_cond_t	start_cond;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	exit_mutex;
	
	long			nbr_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			limiter;
	int				ready_count;

	long			start;

	bool			start_flag;
	bool			exit;
} ;

void	set_data(t_cave	*cave, char **input);

// set_the_table

void	set_struct(t_cave *cave);

// mutex_handl

void	mutex_handln(t_mutex *mutex, t_lockenum lockset);

// lonely_philo

void	lonely_philo(t_cave * cave);

// start_thinking

void	start_thinking(t_cave *cave);

// routine

void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	*routine(void *data);

// eating

void	eating(t_philo *philo);
void	handle_forks(t_philo *philo);

// situation_checker

void	the_great_overseer(t_cave *cave);
long	current_time(void);
bool	situation(t_philo *philo);

// clean_n_errors

bool	check_input(char **input);
void	*malloc_and_bu(size_t bytes);

//helpers

bool	is_number(char *str);
long	ft_latoi(const char *str);

//cleanup

void	clean_cave(t_cave *cave);

#endif
