/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:41:06 by iniska            #+#    #+#             */
/*   Updated: 2024/09/06 20:34:09 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


static long	set_time(const char *input)
{
		long	time;

		time = 0;
		while(*input)
		{
			time = (time * 10) + (*input - '0');
			input++;
		}
		return(time);

}

static void	time_settings(t_cave *cave, char **input)
{
	cave->time_to_die = set_time(input[2]) * 1000; // or 1e3 to get the time
	cave->time_to_eat = set_time(input[3]) * 1000;
	cave->time_to_sleep = set_time(input[4]) * 1000;
	if (cave->time_to_die < 6000 || cave->time_to_eat < 6000 || cave->time_to_sleep < 6000)
	{
		printf("We need a bit more thime than that!\n");
		//clean)struct();
		exit (1);
	}
}

void	set_data(t_cave	*cave, char **input)
{
	if(!check_input(input))
	{
		printf("Funky input\n");
		exit(1);
	}
	cave->nbr_of_philo = set_time(input[1]);
	{
		//make a checker here
		if(cave->nbr_of_philo > 200)
		{
			printf("Too many thinkers\n");
			exit (1);
		}
		//ft_printf("Number of philos: %d\n", cave->nbr_of_philo);
	}
	time_settings(cave, input);
	if(input[5] != NULL)
	{
		cave->limiter = atoi(input[5]); // pickup atoi
		if(cave->limiter <= 0)
		{
			printf("It is said, that philos have to eat at least once\n");
			//clean_the_sturct();
			exit (1);
		}
	}
	set_struct(cave);
	pthread_mutex_init(&cave->start_lock, NULL);
	pthread_cond_init(&cave->start_cond, NULL);
	cave->start_flag = false;
}