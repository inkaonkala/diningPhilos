/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 09:35:34 by iniska            #+#    #+#             */
/*   Updated: 2024/10/07 14:07:18 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lonely_philo(t_cave *cave)
{
	long	time;

	usleep(cave->time_to_die * 1000);
	time = current_time();
	printf("%ld 1 died\n", time);
	clean_cave(cave);
	exit (0);
}