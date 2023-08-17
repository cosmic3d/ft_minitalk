/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:58:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/17 19:47:24 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minitalk.h"

int	g_bitcount;

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	int					str_len;
	struct sigaction	sa;

	if (argc != 3)
		f_exit("Argument count is incorrect");
	if (!check_pid(argv[1]))
		f_exit("Process id is incorrect");
	sa.sa_sigaction = message_sended;
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
		f_exit("Failed when trying to establish a signal action");
	g_bitcount = 0;
	pid = ft_atoi(argv[1]);
	str_len = ft_strlen(argv[2]);
	send_info(pid, str_len, 32);
	i = -1;
	while (++i < str_len)
		send_info(pid, argv[2][i], 8);
	pause();
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
	if (g_bitcount == 0)
		pause();
	usleep(500);
	return ;
}

void	send_info(int pid, int data, int bits)
{
	int	i;

	i = -1;
	while (++i < bits)
	{
		send_bit(pid, data >> i & 1);
		g_bitcount++;
	}
}

void	message_sended(int signal, siginfo_t *info, void *context)
{
	if (g_bitcount == 0)
		return ;
	if (signal == SIGUSR2)
	{
		ft_printf("%sMessage received by %i%s\n", VERDE, info->si_pid, RESET);
		ft_printf("%sTotal bits received: %s", VERDE, RESET);
		ft_printf("%s%i%s\n", CYAN, g_bitcount, RESET);
		return ;
	}
	ft_printf("%s%i: Another client is sending a message. Try again later%s\n", AMARILLO, info->si_pid, RESET);
	context = NULL;
	if (!context)
		exit(1);
	exit(1);
}
