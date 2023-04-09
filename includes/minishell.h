/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:43:28 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/09 04:12:49 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<fcntl.h>
# include<sys/wait.h>
# include<signal.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <paths.h>
# include"../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

extern int	g_exit_status;

enum
{
	SQUOTE = '\'',
	DQUOTE = '\"',
	REDIN = '<',
	REDOUT = '>',
	APPEND = -124,
	HEREDOC = -120,
	PIPE = '|',
	EXPAND_ = '$',
	EMPTY = 0,
	KEYWORD = 1,
	INVALID = -1,
};

typedef struct s_ref
{
	int	i;
	int	j;
	int	l;
}	t_ref;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_tokens
{
	char			*lex;
	int				type;
	int				attach;
	int				lenght;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}	t_tokens;

typedef struct s_exec
{
	char			**str;
	char			*cmd_status;
	int				in_file;
	int				out_file;
	struct s_exec	*next;
}	t_exec;

typedef struct s_pipe
{
	int	p_c;
	int	**p_fd;
}	t_pipe;

typedef struct s_vars
{
	t_exec	*tmp;
	int		*pids;
	int		status;
	int		*std;
	int		i;
}	t_vars;

typedef struct s_data
{
	char		**envp_;
	t_env		*env;
	char		*line;
	t_tokens	*tokens;
	t_exec		*cmds;
	int			check;
	char		*err;
	t_pipe		*pipex;
	char		path[PATH_MAX];
	char		*path_;
	int			heredoc;
}	t_data;

int			main(int ac, char **av, char **envp);
t_exec		*parser(t_data *data);
t_tokens	*lexer(t_data *data);
int			is_keyword(char c);
int			is_quoted(char c);
int			is_whitespace(char c);
int			is_special_op(char c);
int			is_metecharacter(int type);
int			white_space(t_data *data, char *lexem);
int			quotes(t_data *data, char *lexem, char type);
int			quotes_size(char *lexem, char type);
int			expand(t_data *data, char *lexem);
int			expand_size(char *lexem);
int			keyword(t_data *data, char *lexem);
int			special_op(t_data *data, char *lexem, int type);
void		optype(t_data *data, int type);
void		split_token(t_data *data);
int			q_keyword(t_data *data, char *lexem);
void		init_tokens_list(t_data *data);
void		create_new_node(t_data *data, int *add_node);
void		add_new_node(t_data *data);
int			free_tokens_list(t_data *data);
void		cmd_call(t_data *data);
int			count_pps(t_exec	*exec);
void		updt_shlvl(t_data *data);
void		set_environment(t_data *data, char **envp);
void		set_environment_beta(t_data *data);
void		init_env_list(t_data *data, char **envp);
void		add_node(t_data *data, int *new_node);
int			fill_name(t_data *data, char *envp);
int			fill_value(t_data *data, char *envp);
int			free_env_list(t_data *data);
t_tokens	*syntax_analyzer(t_data *data);
void		analyze_begin_end(t_data *data);
void		analyze_begin(t_data *data);
void		analyze_end(t_data *data);
void		analyze_pipe(t_data *data);
void		analyze_redirections(t_data *data);
void		analyze_filename(t_data *data);
int			analyze_quotes(t_data *data);
int			quotes_syntax(t_data *data, char *lexem, int type);
void		abs_syntax(t_data *data, int lexem_len, int n_quotes);
t_tokens	*expander(t_data *data);
void		expand_handler(t_data *data);
char		*free_old_lex(t_data *data);
char		*handle_dolar_sign(char *lexem, int *index);
void		expandable(t_data *data, char *lexem, char *pids);
void		unexpandable(t_data *data, char *lexem, char *pids);
void		non_param(t_data *data, char *lexem, char *str_pid);
char		*get_var(t_data *data, char *lexem);
char		*get_value(t_data *data, char *var);
void		var_exist(t_data *data, char *pids, char *value);
void		var_not_exist(t_data *data, char *lexem, char *pids);
int			update_size(char *lexem, char *pids, char *value, char *e_status);
int			update_size_(char *lexem, char *pids);
t_exec		*tokens_to_cmds(t_data *data);
char		**get_cmd_args(t_data *data);
int			redirections_handler(t_data *data);
void		next_cmd(t_data *data);
int			get_size(t_data *data);
int			redin_handler(t_data *data);
void		redout_handler(t_data *data);
void		append_handler(t_data *data);
int			heredoc_handler(t_data *data);
void		init_cmds_list(t_data *data);
int			is_redirection(int type);
int			free_cmds_list(t_data *data);
void		ft_echo(t_exec *exec);
int			builtin(t_data *data, t_exec *cmd);
int			count_pps(t_exec *exec);
void		signals_handler(void);
void		handle_loop(t_vars pipe, t_data *data);
int			*save_std(void);
int			**pipe_gener(int count);
void		red_inp(t_exec *tmp, int status, t_data *data, int i);
void		close_fd(t_data *data);
int			pipes_redirection(t_exec *tmp, int i, t_data *data);
void		exec_pipes(t_exec *exc, t_data *data);
void		pipe_exe(int *pids, t_data *data, t_exec *tmp, int i);
void		restore_parent(int *stds, int status, int *pids, t_data *data);
void		handle_fds(t_data *data, int i);
void		ft_exit(t_exec *cmd);
void		ft_export(t_data *data, t_exec *cmd);
void		export1(t_data *data, char *name, char *value, bool append);
t_env		*sort_environment(t_data *data);
int			error_in(const char *str);
void		setLastNode(t_env *env);
t_env		*find_node(char *str, t_data *data);
void		ft_unset(t_exec *cmd, t_data *data);
void		execute_command(t_exec *exec, char *path, char **envp);
void		ignore_signal(void);
char		*get_path(char *str, t_data *data, int *status);
void		print_env(t_data *data);
t_env		*sort_environment(t_data *data);
void		restore_parent(int *stds, int status, int *pids, t_data *data);
void		close_fd(t_data *data);
char		*ft_getenv(t_data *data, char *str);
int			ft_pwd(t_data *data);
void		ft_cd(t_data *data);
char		*ft_getenv(t_data *data, char *str);
void		export0(t_data *data);
char		**list_to_str(t_env *env);
void		free_array(char **array);
char		*ft_strjoin_free1(char *s1, char *s2);
int			check_file(const char *filename);
void		shell_cmd(t_data *data, char *path, char **tmp);
void		executable_f(t_data *data, char **tmp);
void		is_directory(t_data *data, t_exec *tmp);
void		is_perms(t_data *data, t_exec *tmp);
void		is_no_such_file(t_data *data, t_exec *tmp);
void		is_no_cmd(t_data *data, t_exec *tmp);
void		cmd_extra(t_data *data, char *path, char **tmp, int st);
void		mini_execve(char *path, t_exec *tmp, char **envp, int i);
void		close_fds(t_data *data);
void		file_checker(char *path, t_data *data, t_exec *tmp, char **envp);
int			check_append(char *str);
char		*extract_name(char *str, bool *append);
char		*extract_value(char *str);
t_env		*find_env_node(t_env *env, const char *name);
void		append_env(t_data *data, const char *name, const char *val);
t_env		*new_env_node(char *name, char *value);
void		add_back_env_node(t_env **env, t_env *new_node);
char		*ft_substr_free1(char *s1, int start, int end);
void		check_bash(char *path, t_exec *exc, char **envp);
void		free_env(t_env *env);
t_env		*str_to_list(char **envp);
void		is_empty(t_data *data, t_exec *exec);
void		error_display(t_exec *tmp);
void		exit_minishell(t_data *data, char *err);
char		*ft_strdup_free(char *s1);
void		free_data(t_data *data);
void		generate_error(t_data *data);
int			white_check(char *str);
char		**ft_2strdup(char **tab1);
void		display_tokens(t_tokens *token);
void		display_table(char **dstr);
void		display_cmds(t_exec *cmds);
void		display_environment(t_data *data);

#endif
