/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:27:56 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/01 18:52:04 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minitalk.h"

int	g_bitcount;

int	main(void)
{
	struct sigaction	sa;

	init_server();
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
		f_exit("Failed when trying to establish a signal action");
	while (1)
		pause();
	return (0);
}

void	init_server(void)
{
	int	pid;

	g_bitcount = 0;
	pid = getpid();
	if (!pid)
		f_exit("Failed when trying to obtain the server process id");
	ft_printf("Server initiated and running\nPID: %d\n", pid);
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	len = 0;
	static int	c = 0;
	static char	*str;

	unused(context);
	signal2bin(&signal);
	if (g_bitcount < 32)
	{
		len |= (signal & 1) << g_bitcount;
		g_bitcount++;
		if (g_bitcount < 32)
			return ;
		str = (char *)malloc(sizeof(char) * (len + 1));
		ft_bzero(str, len + 1);
		if (!len)
		{
			message_ended(str, info);
			len = 0;
			c = 0;
		}
		return ;
	}
	c = reconstruct_string(str, c, signal);
	if (c == len)
	{
		message_ended(str, info);
		len = 0;
		c = 0;
	}
}

int	reconstruct_string(char *str, int c, int signal)
{
	static unsigned int	bit = 0;

	str[c] |= (signal & 1) << bit;
	bit++;
	g_bitcount++;
	if (bit == 8)
	{
		bit = 0;
		return (c + 1);
	}
	return (c);
}

void	message_ended(char *str, siginfo_t *info)
{
	ft_printf("-> %s\n", str);
	usleep(1000);
	kill(info->si_pid, SIGUSR2);
	free(str);
	g_bitcount = 0;
}
