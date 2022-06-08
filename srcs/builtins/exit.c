/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:41:17 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 14:41:21 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

int	get_len(char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arg[i] && ((arg[i] >= 7 && arg[i] <= 13) || arg[i] == ' '))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i] && arg[i] == '0')
		i++;
	while (ft_isdigit(arg[i]))
	{
		len++;
		i++;
	}
	return (len);
}

int	check_exit_value(char *s)
{
	int					i;
	unsigned long long	result;
	unsigned long long	long_long_max;

	i = 0;
	result = 0;
	long_long_max = 9223372036854775807;
	if (s[i] && (s[i] == '-' || s[i] == '+'))
		i++;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - 48);
		i++;
	}
	if (s[0] == '-' && (result - 1) > long_long_max)
		return (1);
	else if (s[0] != '-' && result > long_long_max)
		return (1);
	return (0);
}

int	check_long_long(char *arg)
{
	int	len;

	len = get_len(arg);
	if (len > 19)
		return (1);
	else if (len == 19)
	{
		if (check_exit_value(arg))
			return (1);
	}
	return (0);
}

int	check_exit_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && ((arg[i] >= 7 && arg[i] <= 13) || arg[i] == ' '))
		i++;
	if (!arg[i])
		return (1);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i] || arg[i] == '+' || arg[i] == '-')
		return (1);
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i] && !(arg[i] >= 7 && arg[i] <= 13) && arg[i] != ' ')
		return (1);
	while (arg[i] && ((arg[i] >= 7 && arg[i] <= 13) || arg[i] == ' '))
		i++;
	if (arg[i])
		return (1);
	if (check_long_long(arg))
		return (1);
	return (0);
}

int	exit_cmd(char **args, t_data *data)
{
	if (!args[1])
	{
		ft_putstr_fd("exit\n", 1);
		free_all(data);
		exit(g_exit_status);
	}
	if (check_exit_arg(args[1]))
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_all(data);
		exit(2);
	}
	else if (args[2])
		return (ft_putstr_fd("exit\nminishell: \
exit: too many arguments\n", 2), 1);
	else
	{
		ft_putstr_fd("exit\n", 1);
		g_exit_status = ft_atoll(args[1]);
		free_all(data);
		exit(g_exit_status);
	}
}
