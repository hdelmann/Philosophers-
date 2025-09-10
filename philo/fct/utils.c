/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:21:44 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/09 12:39:20 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	ft_usleep(int i, t_gen *gen)
{
	int	init_time;
	int	final_time;

	(void)gen;
	init_time = ft_time();
	final_time = ft_time() + i;
	while (init_time < final_time)
	{
		usleep(50);
		init_time = ft_time();
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	nbr;

	i = 0;
	s = 1;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\f'
		|| str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		s = -s;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = (str[i] - '0') + (nbr * 10);
		else
			break ;
		i++;
	}
	return (nbr * s);
}

void	printfmutex(char *s, pthread_mutex_t *printff, int i, int start)
{
	pthread_mutex_lock(printff);
	printf(s, (ft_time() - start), i);
	pthread_mutex_unlock(printff);
}

int	ft_isdigit(char *a)
{
	int	i;

	i = 0;
	while (a[i] != '\0')
	{
		if (a[i] < 48 || a[i] > 57)
			return (1);
		i++;
	}
	return (0);
}
