/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thinking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:40:52 by iniska            #+#    #+#             */
/*   Updated: 2024/09/30 20:58:21 by iniska           ###   ########.fr       */
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

static void	set_table(t_cave *cave)
{
	int	i;

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
}

static void	start_lock(t_cave *cave)
{
	int	i;

	i = 0;
	while (i < cave->nbr_of_philo)
	{
		cave->philos[i].last_food_time = cave->start;
		i++;
	}
	pthread_mutex_lock(&cave->start_lock);
	cave->start_flag = false;
}

void	start_thinking(t_cave *cave)
{
	int		i;
	long	last_meal_time;

	cave->start = current_time();
	cave->exit = false;

	start_lock(cave);
	set_table(cave);
	
	// START LOCK
	cave->start_flag = true;
	pthread_cond_broadcast(&cave->start_cond); // signal philos to start
	pthread_mutex_unlock(&cave->start_lock);


	// monitor LOOP
	while (!cave->exit)
	{
		int i = 0; //AASIGNMENT!!!!
		while (i < cave->nbr_of_philo)
		{
			dprintf(2, "Philo %d last food time: %ld, current time: %ld\n", cave->philos[i].id_nmb, cave->philos[i].last_food_time, current_time());
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
		usleep(5000); // the wait delay, bigger num beter cpu usage
	}

	// waiting loop
	i = 0;
	while (i < cave->nbr_of_philo)
	{
		if(cave->exit == true)
			return ;
		//join threads
		dprintf(2, "Philo %d: third check, joining threads\n", cave->philos[i].id_nmb);
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