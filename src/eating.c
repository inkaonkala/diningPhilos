/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:39:58 by iniska            #+#    #+#             */
/*   Updated: 2024/10/07 13:40:35 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

void	handle_forks(t_philo *philo)
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