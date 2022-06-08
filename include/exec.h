/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:17:20 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 16:17:23 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

int		check_builtins(t_cmd *lst);
int		is_only_builtin(t_data *data);
int		loop(t_data *data, char **envp);
int		exec_builtins(t_cmd *lst, t_data *data);
int		executable_error(t_cmd *lst, t_data *data);
int		exit_fork(t_cmd *lst, t_data *data, int ret);
void	print_sig_error_exec(int status);
void	link_pipe(t_cmd *lst, t_data *data);
void	exec_error(char *msg, t_data *data);
void	start_exec(t_cmd *lst, t_data *data);

#endif
