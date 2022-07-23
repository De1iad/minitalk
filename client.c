/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:34:08 by obibby            #+#    #+#             */
/*   Updated: 2022/07/23 23:25:38 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "./libft/libft.h"

static int	g_received;

void	receivedsigs(int n)
{
	static int	x;

	g_received = 1;
	if (n == SIGUSR2)
		x++;
	if (n == SIGUSR1)
	{
		ft_printf("Bytes received successfully: %d\n", x / 8);
		exit(0);
	}
	return ;
}

int	binconvert(char c, int pid, int i)
{
	int	n;

	while (i >= 0)
	{
		n = 0;
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_received == 0)
		{
			usleep(100);
			n++;
			if (n == 5)
			{
				write(1, "No response from server.\n", 26);
				exit(1);
			}
		}
		g_received = 0;
		i--;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	n;

	if (argc != 3)
	{
		ft_printf("Incorrect number of arguments!\n");
		return (1);
	}
	i = 0;
	n = ft_atoi(argv[1]);
	signal(SIGUSR1, receivedsigs);
	signal(SIGUSR2, receivedsigs);
	while (argv[2][i])
		binconvert(argv[2][i++], n, 7);
	binconvert(0, n, 7);
	return (0);
}
