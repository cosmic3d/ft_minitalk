/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:26:36 by jenavarr          #+#    #+#             */
/*   Updated: 2023/07/18 19:09:51 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

/* --------------------------------- HEADERS -------------------------------- */
# include "../lib/ft_libft/libft.h"
# include "../lib/ft_printf/inc/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
/* --------------------------------- STRUCTS -------------------------------- */

/* --------------------------------- FUNCS -------------------------------- */

//CLIENT
void	send_info(int pid, int data, int bits);
void	send_bit(int pid, int bit);
//SERVER
void	signal_handler(int signal, siginfo_t *info, void *context);
void	init_server(void);
void	signal2bin(int *signal);
int		reconstruct_string(char *str, int c, int signal);
//BOTH
int		f_exit(char *err_message);
void	unused(void *unused);
int		check_pid(char *str);
int		check_int(char *s);
int		check_limits_when_10(char *str, int sign);
#endif
