/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initroutine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:33 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/10 15:03:42 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	dead_checker(t_gen *gen)
{
	int	i;

	i = 0;
	while (gen->ph.die[0] == 0)
	{
		pthread_mutex_lock(&gen[i].mu.last_eat[i]);
		if (((ft_time() - gen->tt.start_t) - gen->ph.last_eat[i])
			>= gen->tt.tt_die / 1000)
		{
			pthread_mutex_lock(gen->mu.die);
			gen->ph.die[0] = 1;
			pthread_mutex_unlock(gen->mu.die);
			pthread_mutex_lock(gen->mu.printf);
			printf("%d philo %d died\n", (ft_time() - gen->tt.start_t), i);
			pthread_mutex_unlock(&gen[i].mu.last_eat[i]);
			return (1);
		}
		usleep(10);
		pthread_mutex_unlock(&gen[i].mu.last_eat[i]);
		i++;
		if (i == gen->tt.num_of_philo)
			i = 0;
	}
	return (0);
}

void	*ft_routine(t_gen *arg)
{
	int		index;
	int		num_eat;
	t_gen	gen;

	gen = *arg;
	index = gen.ph.idph;
	num_eat = 0;
	if (index % 2 != 0)
		ft_usleep(100, &gen);
	while (1)
	{
		eat(&gen, index);
		num_eat++;
		if (check(gen, num_eat) == 0)
			return (0);
		sleeping(&gen, index);
		printfmutex("%d philo %d is thinking\n",
			gen.mu.printf, index + 1, gen.tt.start_t);
		if (check(gen, num_eat) == 0)
			return (0);
	}
	return (0);
}

void	init_value0(t_gen *gens, char **av)
{
	int	i;

	i = 0;
	gens[0].mu.printf = malloc(sizeof(pthread_mutex_t));
	gens[0].mu.die = malloc(sizeof(pthread_mutex_t));
	gens[0].mu.fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	gens[0].ph.die = malloc(sizeof(int));
	gens[0].mu.last_eat = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	gens[0].ph.last_eat = malloc(sizeof(int) * ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&gens[0].mu.last_eat[i], NULL);
		pthread_mutex_init(&gens[0].mu.fork[i], NULL);
		gens[0].ph.last_eat[i] = 0;
		i++;
	}
	pthread_mutex_init(gens[0].mu.die, NULL);
	pthread_mutex_init(gens[0].mu.printf, NULL);
}

void	init_value2(t_gen *gens, char **av, int ac)
{
	int	i;
	int	start;

	i = 0;
	start = ft_time();
	while (i < ft_atoi(av[1]))
	{
		if (i != 0)
			init_value3(gens, i);
		gens[i].tt.tt_die = ft_atoi(av[2]) * 1000;
		gens[i].tt.tt_eat = ft_atoi(av[3]) * 1000;
		gens[i].tt.tt_sleep = ft_atoi(av[4]) * 1000;
		gens[i].tt.start_t = start;
		gens[i].ph.die[0] = 0;
		gens[i].tt.num_of_philo = ft_atoi(av[1]);
		gens[i].ph.idph = i;
		if (ac == 6)
		{
			gens[i].tt.num_must_eat = ft_atoi(av[5]);
		}
		i++;
	}
}

void	init_value3(t_gen *gens, int i)
{
	gens[i].ph.last_eat = gens[0].ph.last_eat;
	gens[i].mu.printf = gens[0].mu.printf;
	gens[i].mu.fork = gens[0].mu.fork;
	gens[i].ph.die = gens[0].ph.die;
	gens[i].mu.die = gens[0].mu.die;
	gens[i].ph.last_eat = gens[0].ph.last_eat;
	gens[i].mu.last_eat = gens[0].mu.last_eat;
}
