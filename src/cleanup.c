/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:24:56 by iniska            #+#    #+#             */
/*   Updated: 2024/10/09 10:24:18 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_cave(t_cave *cave)
{
	int	i;

	i = 0;
	if (cave->forks)
	{
		while (i < cave->nbr_of_philo)
		{
			pthread_mutex_destroy(&cave->forks[i].fork);
			i++;
		}
		free(cave->forks);
		cave->forks = NULL;
	}
	i = 0;
	if (cave->philos)
	{
		while (i < cave->nbr_of_philo)
		{
			pthread_join(cave->philos[i].thread_id, NULL);
			i++;
		}
		free(cave->philos);
		cave->philos = NULL;
	}
}
