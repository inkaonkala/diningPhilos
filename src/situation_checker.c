/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   situation_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:44:53 by iniska            #+#    #+#             */
/*   Updated: 2024/10/02 19:05:46 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	current_time(void)
{
	struct  timeval	time;
	long	millis;

	gettimeofday(&time, NULL);
	millis = (int64_t)(time.tv_sec) * 1000 + (time.tv_usec / 1000);

	return (millis);
	
}

bool	situation(t_philo *philo)
{
	if (philo->dead)// || philo->cave->limiter >= philo->meals_eatn) // meals eatn are enough
	{
		philo->cave->exit = true;
		return (false);
	}
	return (true);
}

/*
void	*the_great_overseer(t_cave *cave)
{
	int		i;
	long	last_meal_time;

	i = 0;
	while (!cave->exit)
	{
		i = 0;
		dprintf(2, "number of philo is: %ld\n", cave->nbr_of_philo);
		while (i < cave->nbr_of_philo)
		{
			dprintf(2, "Philo %d last food time: %ld, current time: %ld\n", cave->philos[i].id_nmb, cave->philos[i].last_food_time, current_time());
			dprintf(2, "		second check\n");
			pthread_mutex_lock(&cave->philos[i].time_lock);
			last_meal_time = current_time() - cave->philos[i].last_food_time;
			pthread_mutex_unlock(&cave->philos[i].time_lock);
			if (last_meal_time >= cave->time_to_die)
			{
				printf("Philo %d is DEAD\n", cave->philos[i].id_nmb); // change to time X died
				cave->philos[i].dead = true;
				cave->exit = true;
				return ;
			}
			i++;
		}
		usleep(1000); // the wait delay, bigger num beter cpu usage
	}	
}
*/
