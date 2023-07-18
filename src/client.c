/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:58:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/07/18 20:04:54 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minitalk.h"

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		f_exit("Argument count is incorrect");
	if (!check_pid(argv[1]))
		f_exit("Process id is incorrect");
	pid = ft_atoi(argv[1]);
	send_length(pid, strlen(argv[2]));
	return (0);
}

void	send_bit(int pid, int bit)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) < 0)
			f_exit("Error");
	}
	else
	{
		if (kill(pid, SIGUSR2) < 0)
			f_exit("Error");
	}
	write(1, "Signal sended\n", 15);
	usleep(200);
	return ;
}

void	send_length(int pid, int len)
{
	int	i;

	i = -1;
	while (++i < 32)
		send_bit(pid, len >> i & 1);
}
