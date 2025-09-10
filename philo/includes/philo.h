/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 10:55:51 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/09 12:43:38 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>

typedef struct s_time_to {
	int	tt_die;
	int	num_of_philo;
	int	tt_eat;
	int	tt_sleep;
	int	num_must_eat;
	int	start_t;
}	t_time_to;

typedef struct s_mutex {
	pthread_mutex_t	*fork;
	pthread_mutex_t	*printf;
	pthread_mutex_t	*last_eat;
	pthread_mutex_t	*idph;
	pthread_mutex_t	*die;
}	t_mutex;

typedef struct s_philo {
	pthread_t	phi;
	pthread_t	dead;
	pthread_t	eat;
	int			good_eat;
	int			idph;
	int			*last_eat;
	int			*die;
}	t_philo;

typedef struct s_gen {
	t_time_to	tt;
	t_mutex		mu;
	t_philo		ph;
}	t_gen;

void	init_value0(t_gen *gens, char **av);
void	printfmutex(char *s, pthread_mutex_t *printff, int i, int start);
void	ft_usleep(int i, t_gen *gen);
int		ft_time(void);
void	eat(t_gen *gen, int i);
void	sleeping(t_gen *gen, int i);
int		ft_isdigit(char *a);
void	free_final(t_gen *gen);
void	init_value2(t_gen *gens, char **av, int ac);
void	init_value3(t_gen *gens, int i);
void	init_value(int ac, char **av);
void	*ft_routine(t_gen *arg);
int		dead_checker(t_gen *gen);
int		check(t_gen gen, int num_eat);
int		ft_atoi(const char *str);

#endif