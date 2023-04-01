/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:27 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/01 17:41:09 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <paths.h>
#include"../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>

extern int exitS;

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
    SEMICOLONE = ';',
    AND = '&',
    EMPTY = 0,
    KEYWORD = -1,
};

typedef struct  s_ref
{
    int i;
    int j;
    int l;
}               t_ref;

typedef struct  s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
}               t_env;

typedef struct  s_tokens
{
    char                *lex;
    int                 type;
    int                 lenght;
    struct s_tokens     *next;
    struct s_tokens     *prev;
}               t_tokens;

typedef struct  s_exec
{
    char **str;
    char *flg;
    int in_file;
    int out_file;
    struct s_exec *next;
}               t_exec;

typedef struct  s_pipe
{
    int p_c;
    int **p_fd;
}               t_pipe;

typedef struct  s_vars
{
    t_exec *tmp;
    int *pids;
    int status;
    int *std;
    int i;
}               t_vars;

typedef struct  s_data
{
    char        *buffer;
    char        **envp_;
    t_env       *env;
    t_tokens    *tokens;
    t_exec      *cmds;
    char        *err;
    t_pipe      *pipex;
    char        path[PATH_MAX];
    int         heredoc;
}               t_data;


//---------------------------------/ PARSING PART /--------------------------------------//

int     main(int ac, char **av, char **envp);
t_exec  *parser(t_data *data);

//////////////////////////////// LEXER ///////////////////////////////////////////

t_tokens    *lexer(t_data *data);    
int         is_keyword(char c);
int         is_quoted(char c);
int         is_whitespace(char c);
int         is_special_op(char c);
int         is_metecharacter(int type);
int         white_space(t_data *data, char *lexem);
int         quotes(t_data *data, char *lexem, char type);
int         expand(t_data *data, char *lexem);
int         keyword(t_data *data, char *lexem);
int         special_op(t_data *data, char *lexem, int type);
void        optype (t_data *data, int type);
void        split_token(t_data *data);
int         q_keyword(t_data *data, char *lexem);
void        init_tokens_list(t_data *data);
void        create_new_node(t_data *data, int *add_node);
void        add_new_node(t_data *data);
void        free_tokens_list(t_data *data);
void        cmd_call(t_data *data, int her_file);
int         count_pps(t_exec	*exec);
void        updt_shlvl(t_data *data);

///////////////////////////////// ENVIRONMENT /////////////////////////////////

void        set_environment(t_data *data, char **envp);
void        init_env_list(t_data *data);
void        add_node(t_data *data, int *new_node);
int         fill_name(t_data *data, char *envp);
int         fill_value(t_data *data, char *envp);
void        free_env_list(t_data *data);

///////////////////////////////// SYNTAX ANALYZER //////////////////////////////

t_tokens    *syntax_analyzer(t_data *data);
void        analyze_begin_end(t_data *data);
void        analyze_pipe(t_data *data);
void        analyze_redirections(t_data *data);
int         analyze_quotes(t_data *data);
int         quotes_syntax(char *lexem, int type);
void        abs_syntax(t_data *data, int lexem_len, int n_quotes);
void        analyze_begin(t_data *data, t_tokens *token);
void        analyze_end(t_data *data, t_tokens *token);
    
///////////////////////////////// EXPANDER //////////////////////////////////////

t_tokens    *expander(t_data *data);
void        expand_handler(t_data *data);
char        *free_old_lex(t_data *data);
int         handle_dolar_sign(char *lexem, char **pids);
void        expandable(t_data *data, char *lexem, char *pids);
void        unexpandable(t_data *data, char *lexem, char *pids);
void        non_param(t_data *data, char *lexem, char *str_pid);
char        *get_var(t_data *data, char *lexem);
char        *get_value(t_data *data, char *var);
void        var_exist(t_data *data, char *pids, char *value);
void        var_not_exist(t_data *data, char *lexem, char *pids);
int         update_size(char *lexem, char *pids, char *value, char *e_status);
int         update_size_(char *lexem, char *pids);

/////////////////////////////////// PARSER //////////////////////////////////

t_exec      *tokens_to_cmds(t_data *data);
char        **get_cmd_args(t_data *data);
int         redirections_handler(t_data *data);
void        next_cmd(t_data *data);
int         get_size(t_data *data);
int         redin_handler(t_data *data);
void        redout_handler(t_data *data);
void        append_handler(t_data *data);
int         heredoc_handler(t_data *data);
void        init_cmds_list(t_data *data);
int         is_redirection(int type);
int         free_cmds_list(t_data *data);

//--------------------------------- EXECUTION PART --------------------------//

void    ft_echo(t_exec *exec);
int     builtin(t_data *data, t_exec *cmd);
int     count_pps(t_exec *exec);
void    signals_handler(void);
void    handle_loop(t_vars pipe, int her_file, t_data *data);
int     *save_std(void);
int     **pipe_gener(int count);
void    red_inp(t_exec *tmp, int status, t_data *data, int i);
void    close_fd(t_data *data);
void    handle_loop(t_vars pipe, int her_file, t_data *data);
int     pipes_redirection(t_exec *tmp, int file_, int i, t_data *data);
void    exec_pipes(t_exec *exc, t_data *data, int file_, char **envp_);
void    pipe_exe(int *pids, t_data *data, t_exec *tmp, int i);
void    restore_parent(int *stds, int status, int *pids, t_data *data);
void    handle_fds(t_data *data, int i);
void    ft_exit(t_exec *cmd);
void    ft_export(t_data *data, t_exec *cmd);
void    export1(t_data *data, char *name, char *value, bool append);
t_env   *sort_environment(t_data *data);
int     errorIn(const char *str);
void    setLastNode(t_env *env);
t_env   *find_node(char *str, t_data *data);
void    ft_unset(t_exec *cmd, t_data *data);
void    execute_command(t_exec *exec, char *path, char **envp);
void    ignore_signal();
char    *get_path(char *str, t_data *data, int *status);
void    printEnv(t_data *data);
t_env   *sort_environment(t_data *data);
void    restore_parent(int *stds, int status, int *pids, t_data *data);
void    close_fd(t_data *data);
char    *ft_getenv(t_data *data, char *str);
int     ft_pwd(t_data *data);
void    ft_cd(t_data *data);
char    *ft_getenv(t_data *data, char *str);
void    export0(t_data *data);
char    **list_to_str(t_env *env);

/////////////////////////////////// TOOLS //////////////////////////////////

void            exit_error(t_data *data, char *err, int exit_option);
int             free_data(t_data *data);
int             generate_error(t_data *data);
char            **ft_2strdup(char **str);
int             white_check(char *str);
void            display_tokens(t_tokens *token);
void            display_table(char **dstr);
void            display_cmds(t_exec *cmds);
void            display_environment(t_data *data);

#endif
