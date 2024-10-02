/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:53:04 by iniska            #+#    #+#             */
/*   Updated: 2024/09/30 21:03:11 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(t_philo *philo)
{
	if(!philo->cave->exit)
		printf("TIME %d is thinking\n", philo->id_nmb);
	/*
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
	*/
}

void	eating(t_philo *philo)
{
	if(!philo->cave->exit)
	{
		printf("TIME %d is eating\n", philo->id_nmb);
	
		pthread_mutex_lock(&philo->first_fork->fork);
		pthread_mutex_lock(&philo->second_fork->fork);
		
		philo->last_food_time = current_time();
		usleep(philo->cave->time_to_eat * 1000); // * 1000); // CHECK
		philo->meals_eatn++;

		pthread_mutex_unlock(&philo->first_fork->fork);
		pthread_mutex_unlock(&philo->second_fork->fork);
	}
}

void	sleeping(t_philo *philo)
{
	if(!philo->dead)
		printf("TIME %d is sleeping\n", philo->id_nmb);
	usleep(philo->cave->time_to_sleep * 1000); // * 1000);
}

static void	handle_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->first_fork->fork) == 0)
	{
		usleep(100);
		if(pthread_mutex_lock(&philo->second_fork->fork) == 0)
		{
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
	//waiting for the start
	pthread_mutex_lock(&philo->cave->start_lock);
	while (!philo->cave->start_flag)
		pthread_cond_wait(&philo->cave->start_cond, &philo->cave->start_lock);
	pthread_mutex_unlock(&philo->cave->start_lock);

	while (!philo->cave->exit)
	{
		if(philo_is_dandy && !philo->cave->exit)
			thinking(philo);

		if(philo_is_dandy && !philo->cave->exit)
			handle_forks(philo);
		if(philo_is_dandy && !philo->cave->exit)
			sleeping(philo);

		if (philo->cave->limiter != -1 && philo->meals_eatn >= philo->cave->limiter)
			break ;
	}
	return (NULL);
}
