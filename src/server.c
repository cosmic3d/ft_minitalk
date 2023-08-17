/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:27:56 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/17 21:08:18 by jenavarr         ###   ########.fr       */
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
	static t_client	client;

	if (!manage_client(&client, info, context))
		return ;
	signal2bin(&signal);
	if (g_bitcount < 32)
	{
		client.len |= (signal & 1) << g_bitcount;
		g_bitcount++;
		if (g_bitcount < 32)
			return ;
		client.str = (char *)malloc(sizeof(char) * (client.len + 1));
		ft_bzero(client.str, client.len + 1);
		if (!client.len)
			message_ended(&client, info);
		return ;
	}
	client.c = reconstruct_string(client.str, client.c, signal);
	if (!client.str)
			f_exit("Failed when trying to allocate the memory");
	if (client.c == client.len)
		message_ended(&client, info);
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

void	message_ended(t_client *client, siginfo_t *info)
{
	ft_printf("-> %s\n", client->str);
	usleep(1000);
	kill(info->si_pid, SIGUSR2);
	free(client->str);
	g_bitcount = 0;
	client->len = 0;
	client->c = 0;
	client->client_pid = 0;
}
