/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 09:35:34 by iniska            #+#    #+#             */
/*   Updated: 2024/10/04 09:37:17 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lonely_philo(t_cave *cave)
{
	// CREATE A THREAD AND WAIT TILL DEATH
	printf("I only have one fork, so I do starve to death :(\n");
	clean_cave(cave);
	exit (0);
}