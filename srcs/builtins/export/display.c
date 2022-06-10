
#include "../../../include/minishell.h"

void	print_export(char **dup, t_data *data)
{
	int		i;
	char	**dupdup = NULL ;
	i = -1;
	while (dup[++i])
	{
		dupdup = ft_nsplit(dup[i], '=', 2, data);
		if (!dupdup)
			printf("declare -x %s\n", dup[i]);
		else
			printf("declare -x %s=\"%s\"\n", dupdup[0], dupdup[1]);
		free_strs(dupdup, data);
	}
}

/*gha zedtha*/
// void	print_export_if_no_value(char **dup, t_data *data)
// {
// 	int i;
// 	char **dupdup = NULL;
// 	i = -1;
// 	while(dup[++i])
// 	{
// 		//dupdup = ft_nsplit(dup[i], '=', 2, data);
// 		printf("declare -x %s=\'\'\n", dupdup[0]);

// 		free_strs(dupdup, data);
// 	}
// }

void	sort_export(t_data *data)
{
	char	**dup;
	char	*tmp; 
	int		i;
	int		j;

	dup = dup_env(data->env, data);
	i = -1;
	while (dup[++i])
	{
		j = i;
		while (dup[++j])
		{
			if (ft_strcmp(dup[i], dup[j]) > 0)
			{
				tmp = dup[i];
				dup[i] = dup[j];
				dup[j] = tmp;
			}
		}
	}
	print_export(dup, data);
	free_strs(dup, data);
}