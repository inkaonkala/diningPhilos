/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:53:04 by iniska            #+#    #+#             */
/*   Updated: 2024/10/07 13:42:47 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(t_philo *philo)
{
	long	time;

	time = current_time();
	if(!philo->cave->exit)
		printf("%ld %d is thinking\n", time, philo->id_nmb);
	// test if this makes run smoother
	if (philo->id_nmb % 2 != 0)
		usleep(100);	
}

void	sleeping(t_philo *philo)
{
	long	time;

	time = current_time();
	if(!philo->cave->exit)
		printf("%ld %d is sleeping\n", time, philo->id_nmb);
	usleep(philo->cave->time_to_sleep * 1000);
}

void	*routine(void *data)
{
	t_philo *philo;
	bool	philo_is_dandy; 

	philo = (t_philo *)data;
	philo_is_dandy = situation(philo);

	pthread_mutex_lock(&philo->cave->ready_mutex);
	philo->cave->ready_count++;
	pthread_mutex_unlock(&philo->cave->ready_mutex);
	philo->is_ready = true;
	while(1)
	{
		pthread_mutex_lock(&philo->cave->start_lock);
		if (philo->cave->start_flag)
		{
		//pthread_cond_wait(&philo->cave->start_cond, &philo->cave->start_lock);
			pthread_mutex_unlock(&philo->cave->start_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->cave->start_lock);
	}
	while (!philo->cave->exit)
	{
		if ( philo_is_dandy && !philo->cave->exit)
		{
			thinking(philo);
			handle_forks(philo);
			sleeping(philo);
		}
		if (philo->cave->limiter != -1 && philo->meals_eatn >= philo->cave->limiter)
		{
			pthread_mutex_lock(&philo->cave->exit_mutex);
			philo->cave->exit = true;
			pthread_mutex_unlock(&philo->cave->exit_mutex);
			break ;
		}
	}
	return (NULL);
}
