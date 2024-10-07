/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   situation_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:44:53 by iniska            #+#    #+#             */
/*   Updated: 2024/10/07 11:22:22 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	current_time(void)
{
	struct  timeval	time;
	long	millis;

	gettimeofday(&time, NULL);
	millis = (int64_t)(time.tv_sec) * 1000 + (time.tv_usec / 1000); // this makes everyone live
	return (millis);
}

bool	situation(t_philo *philo)
{
	if (philo->dead)
	{
		philo->cave->exit = true;
		return (false);
	}
	return (true);
}

static void	exit_check(t_cave *cave, int i)
{
	long	time;

	time = current_time();
	if (i == 1)
	{
		printf("%ld %d died\n", time, cave->philos[i].id_nmb); // change to time X died
		cave->exit = true;
		pthread_mutex_unlock(&cave->exit_mutex);
	}
	else if (i == 2)
	{
		cave->full_philos++;
		if(cave->full_philos == cave->nbr_of_philo)
		{
			printf("Philo's are not hungy anymore\n");
			cave->exit = true;
		}
	}	
}

void	the_great_overseer(t_cave *cave)
{
	int	i;
	long	last_meal_time;
	
	i = 0;
	while (i < cave->nbr_of_philo)
	{
		pthread_mutex_lock(&cave->philos[i].time_lock);
		last_meal_time = current_time() - cave->philos[i].last_food_time;
		pthread_mutex_unlock(&cave->philos[i].time_lock);

		if (last_meal_time >= cave->time_to_die)
		{
			printf("	last_meal_time: %ld \n	time_to_die: %ld\n", last_meal_time, cave->time_to_die);
			exit_check(cave, 1);
			break ;
		}
		if (cave->limiter != -1 && cave->philos[i].meals_eatn >= cave->limiter)
		{
			exit_check(cave, 2);
			break ;
		}
		i++;
	}
	//usleep(500);  // the wait delay, bigger num beter cpu usage
	// create better waiting()
}
