/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:17:16 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 16:17:27 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"

int		pwd_cmd(void);
int		echo_cmd(char **args);
int		env_cmd(t_data *data);
int		check_value(char *arg);
int		check_add_value(char *arg);
int		cd_cmd(char **args, t_data *data);
int		exit_cmd(char **args, t_data *data);
int		unset_cmd(char **args, t_data *data);
int		export_cmd(char **args, t_data *data);
int		check_export_arg(char *arg, int *err);
int		check_exist(char *arg, t_env *env, t_data *data);
void	sort_export(t_data *data);
void	update_env_var(t_env *env, char **var, t_data *data);
void	update_add_env_var(t_env *env, char **var, t_data *data);
void	add_env_var(char *arg, t_env **env, int n, t_data *data);
char	*name_without_plus(char *s, t_data *data);

#endif
