/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handln.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:22:19 by iniska            #+#    #+#             */
/*   Updated: 2024/10/09 10:13:18 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	mutex_error(int stat, t_lockenum set)
{
	if (stat == 0)
		return ;
	if (EINVAL == stat && (set == LOCK || set == UNLOCK))
		printf("The value specified by mutex is invalid\n");
	else if (EINVAL == stat && set == INIT)
		printf("The value specified by attr is invalid\n");
	else if (EDEADLK == stat)
		printf("Deadlock accured, blocked philo waiting for fork\n");
	else if (EPERM == stat)
		printf("Current philo does not hold a lock to fork\n");
	else if (ENOMEM == stat)
		printf("Not enough memory to create another mutex\n");
	else if (EBUSY == stat)
		printf("Fork is locked\n");
	exit(1);
}

void	mutex_handln(t_mutex *mutex, t_lockenum lockset)
{
	if (LOCK == lockset)
		mutex_error(pthread_mutex_lock(mutex), lockset);
	else if (UNLOCK == lockset)
		mutex_error(pthread_mutex_unlock(mutex), lockset);
	else if (INIT == lockset)
		mutex_error(pthread_mutex_init(mutex, NULL), lockset);
	else if (DESTROY == lockset)
		mutex_error(pthread_mutex_destroy(mutex), lockset);
	else
	{
		printf("wrong lockset!");
		exit (1);
	}
}
