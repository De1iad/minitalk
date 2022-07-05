/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:34:08 by obibby            #+#    #+#             */
/*   Updated: 2022/07/05 11:58:12 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "./libft/libft.h"

int	binconvert(char c, int pid)
{
	int	i;
	
	i = 7;
	while (i >= 0)
	{
		kill(pid, ((c & (1 << i)) ? SIGUSR1 : SIGUSR2));
		sleep(1/100);
		i--;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int i;
	int	n;
	
	i = 0;
	n = ft_atoi(argv[1]);
	while (argv[2][i])
		binconvert(argv[2][i++], n);
	return (0);
}
