/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handln.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:57:01 by iniska            #+#    #+#             */
/*   Updated: 2024/09/30 10:15:07 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	thread_errors(int stat, t_lockenum set)
{
	if(stat == 0)
		return ;
	else if(EAGAIN == stat)
		printf("No resources to create lock\n");
	else if(EPERM == stat)
		printf("Permission denied from caller\n");
	else if(EINVAL == stat && set == CREATE)
		printf("Attr value is invalid\n");
	else if(EINVAL == stat && (set == JOIN || set == DETACH))
		printf("Thread value is not joinable\n");
	else if(ESRCH == stat)
		printf("No thread found, specify the ID\n");
	else if(EDEADLK == stat)
		printf("A deadlock found, thread calling thread\n");
	else
	{
		printf("This should not come here\n");
		printf("%u\n", set);
	}
	//clean_n_exit()
	//exit(1);
}

void	thread_handl(pthread_t *thread, void *(*foo)(void *), void *data, t_lockenum set)
{
	if (set == CREATE)
		thread_errors(pthread_create(thread, NULL, foo, data), set);
	else if (set == JOIN)
		thread_errors(pthread_join(*thread, NULL), set);	
	else if(set == DETACH)
		thread_errors(pthread_detach(*thread), set);
	else
	{
		printf("False thread code\n");
		exit(1);//clean!
	}	
}