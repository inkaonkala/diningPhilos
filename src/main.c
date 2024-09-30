/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:45:53 by iniska            #+#    #+#             */
/*   Updated: 2024/09/06 20:31:53 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/

static void	cleanup(t_cave *cave)
{
	pthread_mutex_destroy(&cave->start_lock);
	pthread_cond_destroy(&cave->start_cond);
}

int	main(int arc, char **arv)
{
	t_cave	cave;

	if (arc == 5 || arc == 6)
	{
		set_data(&cave, arv);
		printf("Data has been set\n");
		start_thinking(&cave);
		cleanup(&cave);
	}
	else
		printf("You're giving me invalid info!");
	write(1, "BYE!\n", 5);
	return(0);
}