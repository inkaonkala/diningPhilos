/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thinking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:40:52 by iniska            #+#    #+#             */
/*   Updated: 2024/09/27 21:23:39 by iniska           ###   ########.fr       */
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

static long	current_time(void)
{
	struct  timeval	time;
	long	millis;

	gettimeofday(&time, NULL);
	millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);

	return(millis);
	
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

	while (!philo->cave->exit)
	{
		//THINKING
		if(!philo->cave->exit)
			printf("TIME %d is thinking\n", philo->id_nmb);
		if (philo->id_nmb % 2 == 0)
		{
			mutex_handln(&philo->first_fork->fork, LOCK);
			mutex_handln(&philo->second_fork->fork, LOCK);
		}
		else
		{
			mutex_handln(&philo->first_fork->fork, LOCK);
			mutex_handln(&philo->second_fork->fork, LOCK);
		}
		//EATING
		if(!philo->cave->exit)
			printf("TIME %d is eating\n", philo->id_nmb);
		philo->last_food_time = current_time();
		usleep(philo->cave->time_to_eat); // * 1000); // CHECK
		philo->meals_eatn++;

		//UNLOCK FORKS
		mutex_handln(&philo->first_fork->fork, UNLOCK);
		mutex_handln(&philo->second_fork->fork, UNLOCK);

		if(philo->cave->exit)
			break ;
		//SLEEP
		if(!philo->dead)
			printf("TIME %d is sleeping\n", philo->id_nmb);
		usleep(philo->cave->time_to_sleep); // * 1000);

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
	while(i < cave->nbr_of_philo)
	{
		//THIS CRATES THREAD FOR EVERY PHILO
		dprintf(2, "		first check\n");
		thread_handl(&cave->philos[i].thread_id, routine, &cave->philos[i], CREATE);
		i++;
	}
	// START LOCK
	pthread_mutex_lock(&cave->start_lock);
	cave->start_flag = true;
	pthread_cond_broadcast(&cave->start_cond); // signal philos to start
	pthread_mutex_unlock(&cave->start_lock);

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
				dprintf(2, "IN DEAD\n");
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
		//join threadsi
		dprintf(2, "		third check\n");
		thread_handl(&cave->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	//clean()!
	//clean_up(cave);
}