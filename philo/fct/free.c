/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:36:53 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/10 14:58:31 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check(t_gen gen, int num_eat)
{
	pthread_mutex_lock(gen.mu.die);
	if (gen.ph.die[0] == 1)
	{
		pthread_mutex_unlock(gen.mu.die);
		return (0);
	}
	pthread_mutex_unlock(gen.mu.die);
	if (num_eat == gen.tt.num_must_eat)
	{
		gen.ph.die[0] = 2;
		return (0);
	}
	return (1);
}

void	free_final(t_gen *gen)
{
	free(gen->ph.die);
	free(gen->mu.fork);
	free(gen->mu.last_eat);
	free(gen->mu.printf);
	free(gen->mu.die);
	free(gen->ph.last_eat);
	free(gen);
}
