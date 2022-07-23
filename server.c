/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:35:36 by obibby            #+#    #+#             */
/*   Updated: 2022/07/23 23:23:49 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "./libft/libft.h"

void	binrevert(int n, siginfo_t *info, void *ucontext)
{
	static char		c;
	static int		x;
	static int		pid;

	(void)ucontext;
	if (pid == 0)
		pid = info->si_pid;
	if (n == SIGUSR1)
		c = (c << 1) | 1;
	else if (n == SIGUSR2)
		c <<= 1;
	if (++x == 8)
	{
		x = 0;
		if (!c)
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	kill(pid, SIGUSR2);
	return ;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = binrevert;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
