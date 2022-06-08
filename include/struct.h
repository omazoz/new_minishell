/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omazoz <omazoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:17:53 by omazoz            #+#    #+#             */
/*   Updated: 2022/06/06 16:17:55 by omazoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;
typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_opened		t_opened;
typedef struct s_garbage	t_garbage;
typedef struct s_fd_error	t_fd_error;

typedef enum e_token_type
{
	WORD = 1,
	LETTER = 2,
	DQUOTE = '"',
	QUOTE = '\'',
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	DGREATER = 8,
	HERE_DOC = 9,
	DOLLAR = '$',
	WHITE_SPACE = 11,
	IN_DQUOTE = 12,
	IN_QUOTE = 13,
	CMD = 14,
	ARG = 15,
	HERE_DOC_EXPEND = 16
}	t_token_type;

struct	s_garbage
{
	struct s_garbage	*prev;
	void				*ptr;
	struct s_garbage	*next;
};

struct	s_fd_error
{
	struct s_fd_error	*prev;
	char				*content;
	int					errno_nb;
	struct s_fd_error	*next;
};

struct	s_opened
{
	struct s_opened	*prev;
	int				fd;
	struct s_opened	*next;
};

struct	s_cmd
{
	int				in;
	int				out;
	int				error;
	int				pipe[2];
	int				is_builtin;
	char			**cmd;
	char			*cmd_name;
	char			*bin_path;
	pid_t			fork;
	struct s_cmd	*next;
	struct s_cmd	*prev;
};

struct	s_data
{
	int			nb_cmd;
	int			env_i;
	char		**env_char;
	t_env		*env;
	t_cmd		*cmd_lst;
	t_token		*tokens;
	t_opened	*opened;
	t_garbage	*garbage;
	t_fd_error	*fd_error;
};

struct	s_env
{
	struct s_env	*prev;
	char			**var;
	struct s_env	*next;
};

struct	s_token
{
	struct s_token	*prev;
	char			*content;
	t_token_type	type;
	struct s_token	*next;
};

#endif
