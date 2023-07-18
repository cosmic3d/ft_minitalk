/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:51:39 by jenavarr          #+#    #+#             */
/*   Updated: 2023/07/18 18:29:11 by jenavarr         ###   ########.fr       */
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

void	unused(void *unused)
{
	unused = NULL;
	return ;
}

int	check_pid(char *str)
{
	int	j;

	j = 0;
	if (!str[j])
		return (0);
	while (str[j] != '\0')
	{
		if (str[j] < '0' || str[j] > '9')
			return (0);
		j++;
	}
	return (check_int(str));
}

int	check_int(char *s)
{
	int	sign;

	sign = 0;
	if (s[0] == '-' || s[0] == '+')
		sign = 1;
	if (ft_strlen(s) - sign > 10)
		return (0);
	if (ft_strlen(s) - sign == 10)
		if (!check_limits_when_10(s, sign))
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
