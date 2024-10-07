/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thinking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:40:52 by iniska            #+#    #+#             */
/*   Updated: 2024/10/06 22:27:13 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	set_table(t_cave *cave)
{
	int	i;

	i = 0;
	if(cave->nbr_of_philo == 1)
		lonely_philo(cave);
	while(i < cave->nbr_of_philo)
	{
//		cave->philos[i].last_food_time = current_time();	// this makes it infi_loop in second check 	
		if (pthread_create(&cave->philos[i].thread_id, NULL, routine, &cave->philos[i]) != 0)
		{
			printf("Error in creating threads\n");
			return ;
		}
		i++;
	}
	while (1)
	{
		pthread_mutex_lock(&cave->ready_mutex);
		if(cave->ready_count == cave->nbr_of_philo)
		{
			pthread_mutex_unlock(&cave->ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&cave->ready_mutex);
		usleep(100);
	}
	
	// START LOCK
	pthread_mutex_lock(&cave->start_lock);
	cave->start_flag = true;
	pthread_mutex_unlock(&cave->start_lock);
}

static void	start_lock(t_cave *cave)
{
	int	i;

	i = 0;
	cave->start = current_time();
	//pthread_mutex_lock(&cave->start_lock);
	while (i < cave->nbr_of_philo)
	{
		cave->philos[i].last_food_time = cave->start;
		cave->philos[i].is_ready = false;
		i++;
	}
	cave->start_flag = false;
	pthread_mutex_lock(&cave->start_lock);
	cave->start_flag = true;
	pthread_mutex_unlock(&cave->start_lock);
}

void	start_thinking(t_cave *cave)
{
	int		i;
	int		status;

	cave->start = current_time();
	cave->exit = false;
	cave->ready_count = 0;
	pthread_mutex_init(&cave->ready_mutex, NULL);

	start_lock(cave);
	set_table(cave);
	pthread_mutex_unlock(&cave->start_lock);
	cave->start_flag = true;

	pthread_mutex_unlock(&cave->start_lock);

	while (!cave->exit)
		the_great_overseer(cave);
	i = 0;
	while (i < cave->nbr_of_philo)
	{
		printf("in join threads\n");
		status = pthread_join(cave->philos[i].thread_id, NULL);
		if (status != 0)
			printf("ERROR in joining\n");
		i++;
	}
}

