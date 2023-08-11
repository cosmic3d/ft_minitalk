/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:26:36 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/01 18:06:43 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

/* --------------------------------- HEADERS -------------------------------- */
# include "../lib/ft_libft/libft.h"
# include "../lib/ft_printf/inc/ft_printf.h"
# include "colors.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

/* --------------------------------- FUNCS -------------------------------- */
//STRUCTS
typedef struct s_client
{
	int		len;
	int		c;
	char	*str;
	int		client_pid;
}	t_client;
//CLIENT
void	send_bit(int pid, int bit);
void	send_info(int pid, int data, int bits);
void	message_sended(int signal, siginfo_t *info, void *context);
//SERVER
void	signal_handler(int signal, siginfo_t *info, void *context);
void	init_server(void);
int		reconstruct_string(char *str, int c, int signal);
void	message_ended(t_client *client, siginfo_t *info);
//BOTH
int		f_exit(char *err_message);
int		manage_client(t_client *client, siginfo_t *info, void *unused);
int		check_pid(char *str);
int		check_limits_when_10(char *str, int sign);
void	signal2bin(int *signal);

#endif
