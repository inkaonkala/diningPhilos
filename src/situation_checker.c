/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   situation_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:44:53 by iniska            #+#    #+#             */
/*   Updated: 2024/09/30 11:03:25 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	situation(t_philo *philo)
{
	int	i;
	
	i = 0;
	while(i < philo->id_nmb)
	{
		if (philo->dead)
		{
			philo->cave->exit = true;
			return (false);
		}
	}
	return (true);
}