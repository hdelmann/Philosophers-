/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:48:36 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/09 12:56:15 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_destroy(t_gen *gens)
{
	int	i;

	pthread_mutex_destroy(gens[0].mu.printf);
	i = 0;
	while (i < gens->tt.num_of_philo)
	{
		pthread_mutex_destroy(&gens->mu.last_eat[i]);
		pthread_mutex_destroy(&gens->mu.fork[i]);
		i++;
	}
}

void	init_value(int ac, char **av)
{
	int		i;
	t_gen	*gens;

	gens = malloc(sizeof(t_gen) * ft_atoi(av[1]));
	init_value0(gens, av);
	i = 0;
	init_value2(gens, av, ac);
	while (i < gens->tt.num_of_philo)
	{
		if (pthread_create(&gens[i].ph.phi, NULL,
				(void *)ft_routine, &gens[i]) != 0)
			return ;
		i++;
	}
	pthread_create(&gens->ph.dead, NULL, (void *)dead_checker, (void *)gens);
	pthread_join(gens->ph.dead, NULL);
	ft_destroy(gens);
	free_final(gens);
	return ;
}

int	main(int ac, char **av)
{
	int	i;

	i = 1;
	if ((ac != 5 && ac != 6) || ft_atoi(av[1]) == 0)
	{
		printf("wrong arg\n");
		return (0);
	}
	while (i < ac)
	{
		if (ft_isdigit(av[i]) != 0)
		{
			printf("wrong arg\n");
			return (0);
		}
		i++;
	}
	if (ac == 6)
		if (ft_atoi(av[5]) == 0)
			return (0);
	init_value(ac, av);
}
