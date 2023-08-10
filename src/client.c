/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:58:05 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/01 18:47:45 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minitalk.h"

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
	pid = ft_atoi(argv[1]);
	str_len = strlen(argv[2]);
	send_info(pid, str_len, 32);
	i = -1;
	while (++i < str_len)
	{
		send_info(pid, argv[2][i], 8);
		ft_printf("Chars sended: %i\n", i + 1);
	}
	sa.sa_sigaction = message_sended;
	if (sigaction(SIGUSR2, &sa, NULL) < 0)
		f_exit("Failed when trying to establish a signal action");
	while (1)
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
	usleep(400);
	return ;
}

void	send_info(int pid, int data, int bits)
{
	int	i;

	i = -1;
	while (++i < bits)
		send_bit(pid, data >> i & 1);
}

void	message_sended(int signal, siginfo_t *info, void *context)
{
	unused(context);
	unused(&signal);
	ft_printf("%sMessage received by %i%s\n", VERDE, info->si_pid, RESET);
	exit(1);
}
