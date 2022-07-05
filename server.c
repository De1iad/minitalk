/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:35:36 by obibby            #+#    #+#             */
/*   Updated: 2022/07/05 13:03:25 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "./libft/libft.h"

void	binrevert(int n)
{
	static char	c;
	static int	x;

	if (n == 10)
		c = (c << 1) | 1;
	else if (n == 12)
		c <<= 1;
	x++;
	if (x == 8)
	{
		x = 0;
		write(1, &c, 1);
		c = 0;
	}
}

int	main()
{
	struct sigaction sa;
	
	sa.sa_handler = binrevert;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
