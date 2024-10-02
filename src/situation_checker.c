/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   situation_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:44:53 by iniska            #+#    #+#             */
/*   Updated: 2024/09/30 20:57:12 by iniska           ###   ########.fr       */
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
	if (philo->dead)
	{
		philo->cave->exit = true;
		return (false);
	}
	return (true);
}