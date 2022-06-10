
#include "../../../include/minishell.h"

void	do_not_exist(char **args, int i, t_data *data)
{
	if (check_add_value(args[i]))
		add_env_var(args[i], &data->env, 2, data);
	else
		ft_env_addback(data->env, ft_env_lstnew(args[i], NULL, data));
}

void	no_env(char **args, int i, t_data *data)
{
	if (!check_add_value(args[i]))
		data->env = ft_env_lstnew(args[i], NULL, data);
	else
		add_env_var(args[i], &data->env, 1, data);
}

void	free_dup_env_char(t_data *data)
{
	if (data->env_char)
		free_strs(data->env_char, data);
	if (data->env)
		data->env_char = dup_env(data->env, data);
}

int	export_cmd(char **args, t_data *data)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (!args[1] && data->env)
		return (sort_export(data), 0);
	while (args[++i])
	{
		if (args[i] && !check_export_arg(args[i], &error))
		{
			// if (!check_value(args[i]))
			// 	continue ;
			if (!data->env)
			{
				no_env(args, i, data);
				break ;
			}
			if (check_exist(args[i], data->env, data))
				continue ;
			else
				do_not_exist(args, i, data);
		}
	}
	return (free_dup_env_char(data), error);
}
