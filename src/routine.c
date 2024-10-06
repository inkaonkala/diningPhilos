/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:53:04 by iniska            #+#    #+#             */
/*   Updated: 2024/10/06 17:09:26 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(t_philo *philo)
{
	long	time;

	time = current_time();
	if(!philo->cave->exit)
		printf("%ld philo %d is thinking\n", time, philo->id_nmb);
	// test if this makes run smoother
	//if (philo->id_nmb % 2 != 0)
	//	usleep(100);	
}

void	eating(t_philo *philo)
{
	long	time;

	time = current_time();
	if(!philo->cave->exit)
	{
		printf("%ld philo %d is eating\n", time, philo->id_nmb);
	
		pthread_mutex_lock(&philo->time_lock);
		philo->last_food_time = current_time();

		pthread_mutex_unlock(&philo->time_lock);
		
		usleep(philo->cave->time_to_eat * 1000);
		philo->meals_eatn++;
	}
}

void	sleeping(t_philo *philo)
{
	long	time;

	time = current_time();
	if(!philo->dead)
		printf("%ld philo %d is sleeping\n", time, philo->id_nmb);
	usleep(philo->cave->time_to_sleep * 1000);
}

static void handle_forks(t_philo *philo)
{
    if (pthread_mutex_trylock(&philo->first_fork->fork) == 0) {
        if (pthread_mutex_trylock(&philo->second_fork->fork) == 0) {
            eating(philo);
            pthread_mutex_unlock(&philo->second_fork->fork);
        }
        pthread_mutex_unlock(&philo->first_fork->fork);
    }
}

void	*routine(void *data)
{
	t_philo *philo;
	bool	philo_is_dandy; 

	philo = (t_philo *)data;
	philo_is_dandy = situation(philo);

	pthread_mutex_lock(&philo->cave->start_lock);
	while (!philo->cave->start_flag)
		pthread_cond_wait(&philo->cave->start_cond, &philo->cave->start_lock);
	pthread_mutex_unlock(&philo->cave->start_lock);

	while (!philo->cave->exit)
	{
		if ( philo_is_dandy && !philo->cave->exit)
		{
			thinking(philo);
			handle_forks(philo);
			sleeping(philo);
		}
		if (philo->cave->limiter != -1 && philo->meals_eatn >= philo->cave->limiter)
		 break ;
	}
	return (NULL);
}
