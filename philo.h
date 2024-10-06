/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:43:44 by iniska            #+#    #+#             */
/*   Updated: 2024/10/04 09:51:30 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// /.philo filo_count time_die time_eat time_sleep (number_of_meals)

#ifndef	PHILO
# define PHILO

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h> // usleep
# include <limits.h> // int maxs
# include <stdbool.h>
# include <errno.h> // for mutex errors
# include <pthread.h> // for mutex, init, destroy, lock stuff
# include <sys/time.h> // get time


// enums (the unchangable stuff)

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

// our fork is the MUTEX, so every fork is a lock that is opened and closed
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

	pthread_t	thread_id;
	t_cave		*cave;

} t_philo;

//includes all the data
struct s_cave
{
	t_fork	*forks;
	t_philo	*philos;

	int		full_philos;

	t_mutex	start_lock;
	pthread_cond_t start_cond;
	pthread_mutex_t exit_mutex;
	
	long	nbr_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		limiter;

	long	start;

	bool	start_flag;
	bool	exit;
} ;

//parsing

void	set_data(t_cave	*cave, char **input);

// set_the_table

void	set_struct(t_cave *cave);

// mutex_handl

void	mutex_handln(t_mutex *mutex, t_lockenum lockset);

// therad_hndl

void	thread_errors(int stat, t_lockenum set);
void	thread_handl(pthread_t *thread, void *(*foo)(void *), void *data, t_lockenum set);

// lonely_philo

void	lonely_philo(t_cave * cave);

// start_thinking

void	start_thinking(t_cave *cave);

// routine

void	thinking(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	*routine(void *data);

// situation_checker

void	the_great_overseer(t_cave *cave);
long	current_time(void);
bool	situation(t_philo *philo);

// clean_n_errors

bool	check_input(char **input);
void	*malloc_and_bu(size_t bytes);

//helpers

bool	is_number(char *str);

//cleanup
void	clean_cave(t_cave *cave);
#endif
