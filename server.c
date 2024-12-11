/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envillan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:40:56 by envillan          #+#    #+#             */
/*   Updated: 2024/12/11 15:49:59 by envillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_mini	*server_init(void)
{
	t_mini	*talk;

	talk = malloc(sizeof(t_mini));
	if (!talk)
	{
		ft_putstr("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	talk->server_pid = 0;
	talk->client_pid = 0;
	return (talk);
}

void	server_message(char *message)
{
	int		i;
	int		base;
	int		control;
	int		result;
	char	bit;

	i = 7;
	while (message[i])
	{
		base = 1;
		control = i;
		result = 0;
		while (base <= 128)
		{
			bit = message[control];
			if (bit == '1')
				result += base;
			base *= 2;
			control--;
		}
		write(1, &result, 1);
		i += 8;
	}
}

void	binary_store(int signal)
{
	static int	i = 0;
	static char	c[8];

	if (signal == SIGUSR1)
		c[i] = '1';
	else if (signal == SIGUSR2)
		c[i] = '0';
	i++;
	if (i == 8)
	{
		i = 0;
		server_message(c);
	}
}

int	main(int argc, char *argv[])
{
	t_mini	*talk;

	(void)argv;
	talk = NULL;
	if (argc != 1)
	{
		ft_putstr("Error: invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		talk = server_init();
		talk->server_pid = getpid();
		ft_putstr("Server PID: ");
		ft_putnbr(talk->server_pid);
		ft_putstr("\n");
		signal(SIGUSR1, binary_store);
		signal(SIGUSR2, binary_store);
		while (1)
			sleep(1);
	}
	free(talk);
	return (0);
}
