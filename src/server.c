/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:27:56 by jenavarr          #+#    #+#             */
/*   Updated: 2023/07/18 19:40:45 by jenavarr         ###   ########.fr       */
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
	g_bitcount++;
	ft_printf("Se recibió la señal: %d\n", signal);
	unused(context);
	info = NULL;
}
