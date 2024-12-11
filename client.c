/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envillan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:52:05 by envillan          #+#    #+#             */
/*   Updated: 2024/12/11 15:39:05 by envillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_mini	*client_init(void)
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

void	client_message(t_mini *talk, char *message)
{
	int		i;
	int		base;
	char	c;

	i = 0;
	while (message[i])
	{
		base = 128;
		c = message[i];
		while (base > 0)
		{
			if (c >= base)
			{
				kill(talk->server_pid, SIGUSR1);
				c -= base;
			}
			else
				kill(talk->server_pid, SIGUSR2);
			base /= 2;
			usleep(100);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_mini	*talk;

	talk = NULL;
	if (argc != 3)
	{
		ft_putstr("Error: invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		talk = client_init();
		talk->server_pid = ft_atoi(argv[1]);
		if (talk->server_pid <= 0)
		{
			ft_putstr("Error: invalid PID\n");
			free(talk);
			exit(EXIT_FAILURE);
		}
		client_message(talk, argv[2]);
	}
	free(talk);
	return (0);
}
