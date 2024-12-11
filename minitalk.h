/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envillan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:06:13 by envillan          #+#    #+#             */
/*   Updated: 2024/12/11 15:49:15 by envillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_mini
{
	int	server_pid;
	int	client_pid;
}		t_mini;

void	client_message(t_mini *talk, char *message);
void	server_message(char *message);
void	binary_store(int signal);
void	ft_putstr(char *str);
void	ft_putnbr(int number);
t_mini	*client_init(void);
t_mini	*server_init(void);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);

#endif
