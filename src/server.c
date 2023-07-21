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

void imprimirBinario(unsigned int numero) {
    int bits = sizeof(unsigned int) * 8; // Número de bits en un unsigned int

    // Recorre cada bit desde el más significativo hasta el menos significativo
    for (int i = bits - 1; i >= 0; i--) {
        // Verifica si el bit en la posición i es 1 o 0
        if ((numero >> i) & 1) {
            putchar('1');
        } else {
            putchar('0');
        }

        // Agrupa los bits en grupos de 4 para facilitar la lectura
        if (i % 4 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}

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
	static unsigned int	len = 0;
	static char			*str;

	signal2bin(&signal);
	if (g_bitcount < 32)
	{
		len |= (signal & 1) << g_bitcount;
		imprimirBinario(len);
		g_bitcount++;
		if (g_bitcount < 32)
			return ;
		ft_bzero(str, sizeof(char) * (len + 1));
	}
	unused(context);
	info = NULL;
	if (info)
		return ;
	return ;
	g_bitcount++;
}

void	signal2bin(int *signal)
{
	if (*signal == 10)
		*signal = 0;
	else
		*signal = 1;
	return ;
}
