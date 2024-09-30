/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:53:04 by iniska            #+#    #+#             */
/*   Updated: 2024/09/30 11:58:27 by iniska           ###   ########.fr       */
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
