/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:34:08 by obibby            #+#    #+#             */
/*   Updated: 2022/07/05 17:01:43 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "./libft/libft.h"

void	receivedsigs(int n)
{
	static int	x;

	if (n == SIGUSR2)
		x++;
	if (n == SIGUSR1)
	{
		ft_printf("Characters received successfully: %d\n", x/8);
		exit(0);
	}
	return ;
}

int	binconvert(char c, int pid, int i)
{
	while (i >= 0)
	{
		kill(pid, ((c & (1 << i)) ? SIGUSR1 : SIGUSR2));
		i--;
		pause();
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int i;
	int	n;
	
	i = 0;
	n = ft_atoi(argv[1]);
	signal(SIGUSR1, receivedsigs);
	signal(SIGUSR2, receivedsigs);
	while (argv[2][i])
		binconvert(argv[2][i++], n, 7);
	binconvert(0, n, 7);
	return (0);
}
