/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:53:04 by iniska            #+#    #+#             */
/*   Updated: 2024/10/03 20:20:51 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(t_philo *philo)
{
	long	time;

	time = current_time();
	if(!philo->cave->exit)
     printf("%ld %d is thinking\n", time, philo->id_nmb);
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


void	eating(t_philo *philo)
{
	long	time;

	time = current_time();
	if(!philo->cave->exit)
	{
		pthread_mutex_lock(&philo->time_lock);
		philo->last_food_time = time;
		pthread_mutex_unlock(&philo->time_lock);
		printf("%ld %d is eating\n", time, philo->id_nmb);
		usleep(philo->cave->time_to_eat * 1000);
		philo->meals_eatn++;
	}
}

static void	handle_forks(t_philo *philo)
{
	long	time;

	time = current_time();

	pthread_mutex_lock(&philo->first_fork->fork);
	pthread_mutex_lock(&philo->second_fork->fork);
	if(!philo->cave->exit)
		printf("%ld %d has taken a fork\n", time, philo->id_nmb);
	eating(philo);
	pthread_mutex_unlock(&philo->second_fork->fork);
	pthread_mutex_unlock(&philo->first_fork->fork);
	//pthread_mutex_unlock(&philo->second_fork->fork);
}
*/

/*
void	*routine(void *data)
{
	t_philo *philo;
	bool	philo_is_dandy; 

	philo = (t_philo *)data;
	philo_is_dandy = situation(philo);

	if (philo->id_nmb % 2 == 0)
		usleep(100);

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
*/

void	*routine(void *data)
{
	t_philo *philo;
	bool	philo_is_dandy; 



	philo = (t_philo *)data;
	philo_is_dandy = situation(philo);

	printf("in routine\n");
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
