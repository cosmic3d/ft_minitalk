/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:51:39 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/01 18:03:09 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minitalk.h"

int	f_exit(char *err_message)
{
	if (*err_message)
		ft_printf("%s\n", err_message);
	exit(1);
	return (0);
}

int	manage_client(t_client *client, siginfo_t *info, void *unused)
{
	if (info->si_pid == client->client_pid)
		return (1);
	if (client->client_pid != 0)
	{
		kill(info->si_pid, SIGUSR1);
		return (0);
	}
	client->client_pid = info->si_pid;
	client->c = 0;
	client->len = 0;
	client->str = NULL;
	kill(info->si_pid, SIGUSR2);
	unused = NULL;
	if (!unused)
		return (1);
	return (1);
}

int	check_pid(char *str)
{
	int	j;
	int	sign;

	j = 0;
	if (!str[j])
		return (0);
	while (str[j] != '\0')
	{
		if (str[j] < '0' || str[j] > '9')
			return (0);
		j++;
	}
	sign = 0;
	if (str[0] == '-' || str[0] == '+')
		sign = 1;
	if (ft_strlen(str) - sign > 10)
		return (0);
	if (ft_strlen(str) - sign == 10)
		if (!check_limits_when_10(str, sign))
			return (0);
	return (1);
}

int	check_limits_when_10(char *str, int sign)
{
	if (sign)
	{
		if (str[0] == '+')
		{
			if (ft_strncmp(str, "+2147483647", 11) > 0)
				return (0);
		}
		else
		{
			if (ft_strncmp(str, "-2147483648", 11) > 0)
				return (0);
		}
	}
	if (ft_strncmp(str, "2147483647", 10) > 0)
		return (0);
	return (1);
}

void	signal2bin(int *signal)
{
	if (*signal == SIGUSR1)
		*signal = 0;
	else
		*signal = 1;
	return ;
}
