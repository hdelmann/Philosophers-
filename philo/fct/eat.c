/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:26:52 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/09 11:15:46 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleeping(t_gen *gen, int i)
{
	pthread_mutex_lock(gen->mu.printf);
	printf("%d philo %d is sleeping\n", (ft_time() - gen->tt.start_t), i + 1);
	pthread_mutex_unlock(gen->mu.printf);
	ft_usleep(gen->tt.tt_sleep / 1000, gen);
}

void	eat2(t_gen *gen, int i)
{
	pthread_mutex_lock(&gen->mu.fork[i]);
	printfmutex("%d philo %d has taken his fork\n",
		gen->mu.printf, i + 1, gen->tt.start_t);
	pthread_mutex_lock(&gen->mu.fork[i - 1]);
	printfmutex("%d philo %d has taken other fork\n",
		gen->mu.printf, i + 1, gen->tt.start_t);
	pthread_mutex_lock(&gen->mu.last_eat[i]);
	gen->ph.last_eat[i] = ft_time() - gen->tt.start_t;
	pthread_mutex_unlock(&gen->mu.last_eat[i]);
	printfmutex("%d philo %d is eating\n",
		gen->mu.printf, i + 1, gen->tt.start_t);
	ft_usleep(gen->tt.tt_eat / 1000, gen);
	pthread_mutex_unlock(&gen->mu.fork[i]);
	pthread_mutex_unlock(&gen->mu.fork[i - 1]);
}

void	eat(t_gen *gen, int i)
{
	if (i == 0)
	{
		pthread_mutex_lock(&gen->mu.fork[i]);
		printfmutex("%d philo %d has taken his fork\n",
			gen->mu.printf, i + 1, gen->tt.start_t);
		pthread_mutex_lock(&gen->mu.fork[gen->tt.num_of_philo - 1]);
		printfmutex("%d philo %d has taken other fork\n",
			gen->mu.printf, i + 1, gen->tt.start_t);
		pthread_mutex_lock(&gen->mu.last_eat[i]);
		gen->ph.last_eat[i] = ft_time() - gen->tt.start_t;
		pthread_mutex_unlock(&gen->mu.last_eat[i]);
		printfmutex("%d philo %d is eating\n",
			gen->mu.printf, i + 1, gen->tt.start_t);
		ft_usleep(gen->tt.tt_eat / 1000, gen);
		pthread_mutex_unlock(&gen->mu.fork[i]);
		pthread_mutex_unlock(&gen->mu.fork[gen->tt.num_of_philo - 1]);
	}
	else
	{
		eat2(gen, i);
	}
}
