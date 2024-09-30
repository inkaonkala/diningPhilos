/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handln.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:22:19 by iniska            #+#    #+#             */
/*   Updated: 2024/08/27 19:30:54 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// initialize
// destroy
// lock
// unlock

static void	mutex_error(int stat, t_lockenum set)
{
	if (stat == 0)
		return ;
	if (EINVAL == stat && (set == LOCK || set == UNLOCK))
		printf("The value specified by mutex is invalid\n");
		//clean_n_exit
	else if(EINVAL == stat && set == INIT)
		printf("The value specified by attr is invalid\n");
	else if(EDEADLK == stat)
		printf("Deadlock accured, blocked philo waiting for fork\n");
	else if (EPERM == stat)
		printf("Current philo does not hold a lock to fork\n");
	else if (ENOMEM == stat)
		printf("Not enough memory to create another mutex\n");
	else if (EBUSY == stat)
		printf("Fork is locked\n");
	//clean_n_exit();
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
		//clean_n_exit;
		printf("wrong lockset!");
		exit (1);
	}
	//pthread_mutex_init(mutex, NULL);
	///pair it with pthread_mu8tex_destroy(t_mutex, NULL)
}
