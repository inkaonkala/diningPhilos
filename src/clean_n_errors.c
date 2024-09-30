/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:22:39 by iniska            #+#    #+#             */
/*   Updated: 2024/09/30 10:24:03 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


/*
static bool	max_int(char *str)
{
	if(ft_strlen(str) > 10)
		return(false);
	if(strlen(str) == 10)
	{
		if((str[0] < '0' && str[0] > '2') || (str[1] < '0' && str[1] > '1') || ())
			return (false);
	}
		

}
*/

/*
void	exit_with_message(struct, char *str)
{
	printf("%s", string);
	clean_cave(cave); 
	exit (1);
}
*/

static int t_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*malloc_and_bu(size_t bytes)
{
	void	*mal;

	mal = malloc(bytes);
	if (mal == NULL)
	{
		//clean_up();
		exit (1);
	}
	return (mal);
}

bool	check_input(char **input)
{
	int	i;

	i = 1;
	while (input[i])
	{
		if(!is_number(input[i]))
			return (false);
		i++;
	}
	i = 1;
	while (input[i])
	{
		if(t_strlen(input[i]) > 4) // write strlen
		{
			printf("We don't want to spend the whole day with this ... \n");
			return (false);
		}
		i++;
	}
	return (true);
}