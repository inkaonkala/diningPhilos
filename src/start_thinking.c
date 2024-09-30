/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thinking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:40:52 by iniska            #+#    #+#             */
/*   Updated: 2024/09/30 11:56:12 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// input philo_nbr, time_die, time_eat, time_sleep, (plate nbr)

/*
Each philosopher will run a routine where they repeatedly:

Think.
Try to pick up the two forks (mutexes).
Eat.
Put down the forks.
Sleep.
*/

long	current_time(void)
{
	struct  timeval	time;
	long	millis;

	gettimeofday(&time, NULL);
	millis = (int64_t)(time.tv_sec) * 1000 + (time.tv_usec / 1000);

	return (millis);
	
}

static void	*routine(void *data)
{
	t_philo *philo;
	
	philo = (t_philo *)data;

	//waiting for the start
	pthread_mutex_lock(&philo->cave->start_lock);
	while (!philo->cave->start_flag)
		pthread_cond_wait(&philo->cave->start_cond, &philo->cave->start_lock);
	pthread_mutex_unlock(&philo->cave->start_lock);

	if(philo->id_nmb == 1)
		usleep(100);

	while (!philo->cave->exit)
	{
		if(situation(philo))
			thinking(philo);

		if(situation(philo) && !philo->cave->exit)
		{
			if (pthread_mutex_lock(&philo->first_fork->fork) == 0)
			{
				if(pthread_mutex_lock(&philo->second_fork->fork) == 0)
				{
					eating(philo);
					pthread_mutex_unlock(&philo->second_fork->fork);
				}
				pthread_mutex_unlock(&philo->first_fork->fork);
			}
		}
		if(situation(philo) && !philo->cave->exit)
			sleeping(philo);

		if (philo->cave->limiter != -1 && philo->meals_eatn >= philo->cave->limiter)
			break ;
	}
	return (NULL);
}

void	start_thinking(t_cave *cave)
{
	int		i;
	long	last_meal_time;

	cave->start = current_time();
	cave->exit = false;

	i = 0;
	
	while (i < cave->nbr_of_philo)
	{
		cave->philos[i].last_food_time = cave->start;
		i++;
	}
	pthread_mutex_lock(&cave->start_lock);
	cave->start_flag = false;



	// CREATE PHILOS
	i = 0;
	while(i < cave->nbr_of_philo)
	{
//		cave->philos[i].last_food_time = current_time();	// this makes it infi_loop in second check 	
		dprintf(2, "		first check\n");
		thread_handl(&cave->philos[i].thread_id, routine, &cave->philos[i], CREATE);
		i++;
	}
	
	// START LOCK
	cave->start_flag = true;
	pthread_cond_broadcast(&cave->start_cond); // signal philos to start
	pthread_mutex_unlock(&cave->start_lock);


	// CAVE LOOP
	while (!cave->exit)
	{
		i = 0;
		while (i < cave->nbr_of_philo)
		{
			dprintf(2, "		second check\n");
			last_meal_time = current_time() - cave->philos[i].last_food_time;
			if (last_meal_time >= cave->time_to_die)
			{
				printf("Philo %d is DEAD\n", cave->philos[i].id_nmb); // change to time X died
				cave->exit = true;
				//return ;
				break ;
			}
			i++;
		}
		usleep(1000); // the wait delay
	}
	i = 0;
	while (i < cave->nbr_of_philo)
	{
		if(cave->exit == true)
			return ;
		//join threads
		dprintf(2, "		third check\n");
		thread_handl(&cave->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}


/*
void	start_thinking(t_cave *cave)
{
	int		i;
	long	last_meal_time;

	cave->start = current_time();
	cave->exit = false;

	i = 0;
	
	// CREATE PHILOS
	while(i < cave->nbr_of_philo)
	{
//		cave->philos[i].last_food_time = current_time();	// this makes it infi_loop in second check 	
		dprintf(2, "		first check\n");
		thread_handl(&cave->philos[i].thread_id, routine, &cave->philos[i], CREATE);
		i++;
	}
	
	// START LOCK
	pthread_mutex_lock(&cave->start_lock);
	cave->start_flag = true;
	pthread_cond_broadcast(&cave->start_cond); // signal philos to start
	pthread_mutex_unlock(&cave->start_lock);


	// CAVE LOOP
	while (!cave->exit)
	{
		i = 0;
		while (i < cave->nbr_of_philo)
		{
			dprintf(2, "		second check\n");
			last_meal_time = current_time() - cave->philos[i].last_food_time;
			if (last_meal_time >= cave->time_to_die)
			{
				printf("Philo %d is DEAD\n", cave->philos[i].id_nmb); // change to time X died
				cave->exit = true;
				//return ;
				break ;
			}
			i++;
		}
		usleep(1000); // the wait delay
	}
	i = 0;
	while (i < cave->nbr_of_philo)
	{
		if(cave->exit == true)
			return ;
		//join threads
		dprintf(2, "		third check\n");
		thread_handl(&cave->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}

*/