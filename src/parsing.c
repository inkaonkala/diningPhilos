/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:41:06 by iniska            #+#    #+#             */
/*   Updated: 2024/10/06 20:32:56 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_atoi(const char *str)
{
	int	n;
	int	t;

	n = 0;
	t = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			t = -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9'))
	{
		n *= 10;
		n += *str - '0';
		str++;
	}
	return (n * t);
}

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
	cave->time_to_die = set_time(input[2]);
	cave->time_to_eat = set_time(input[3]);
	cave->time_to_sleep = set_time(input[4]);
	printf("time to die is %ld: ", cave->time_to_die);
	if (cave->time_to_die < 60 || cave->time_to_eat < 60 || cave->time_to_sleep < 60)
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
			exit(1);
		}
	}
	time_settings(cave, input);
	if(input[5] != NULL)
	{
		cave->limiter = ft_atoi(input[5]);
		if(cave->limiter <= 0)
		{
			printf("It is said, that philos have to eat at least once\n");
			//clean_cave(cave);
			exit(1);
		}
	}
	set_struct(cave);
	pthread_mutex_init(&cave->start_lock, NULL);
	pthread_cond_init(&cave->start_cond, NULL);
	cave->start_flag = false;
}