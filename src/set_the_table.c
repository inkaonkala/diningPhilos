/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_the_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:06:54 by iniska            #+#    #+#             */
/*   Updated: 2024/10/09 10:05:03 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	hand_the_forks(t_philo *philo, t_fork *fork, int position)
{
	int	id;

	id = philo->cave->nbr_of_philo;
	if ((philo->id_nmb % 2) != 0)
	{
		philo->first_fork = &fork[(position + 1) % id];
		philo->second_fork = &fork[position];
	}
	else
	{	
		philo->second_fork = &fork[position];
		philo->first_fork = &fork[(position + 1) % id];
	}
}

static void	set_philos(t_cave *cave)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < cave->nbr_of_philo)
	{
		philo = cave->philos + i;
		philo->id_nmb = i + 1;
		philo->full = false;
		philo->dead = false;
		philo->is_ready = false;
		philo->meals_eatn = 0;
		philo->cave = cave;
		pthread_mutex_init(&cave->philos[i].time_lock, NULL);
		hand_the_forks(philo, cave->forks, i);
		i++;
	}
}

void	set_struct(t_cave *cave)
{
	int	i;

	i = 0;
	cave->exit = false;
	cave->philos = malloc_and_bu(sizeof(t_philo) * cave->nbr_of_philo);
	cave->forks = malloc_and_bu(sizeof(t_fork) * cave->nbr_of_philo);
	pthread_mutex_init(&cave->exit_mutex, NULL);
	cave->full_philos = 0;
	while (i < cave->nbr_of_philo)
	{
		mutex_handln(&cave->forks[i].fork, INIT);
		cave->forks[i].id_fork = i;
		i++;
	}
	set_philos(cave);
}
