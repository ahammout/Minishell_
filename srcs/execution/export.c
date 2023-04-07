/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:24:41 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/06 21:52:31 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	g_exit_status;

void	append_env(t_data *data, const char *name, const char *val)
{
	char	*new_val;
	size_t	new_val_len ;
	t_env	*node;
	t_env	*new_node;

	node = find_env_node(data->env, name);
	if (node)
	{
		if (node->value)
		{
			new_val_len = ft_strlen(node->value) + ft_strlen(val);
			new_val = malloc(new_val_len + 1);
			ft_strlcpy(new_val, node->value, new_val_len + 1);
			ft_strlcat(new_val, val, new_val_len + 1);
			free(node->value);
			node->value = new_val;
		}
		else
			node->value = ft_strdup(val);
	}
	else
	{
		new_node = new_env_node(ft_strdup(name), ft_strdup(val));
		add_back_env_node(&data->env, new_node);
	}
}

t_env	*new_env_node(char *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	add_back_env_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	export1(t_data *data, char *name, char *value, bool append)
{
	t_env	*node;

	if (append)
	{
		append_env(data, name, value);
		return ;
	}
	node = find_env_node(data->env, name);
	if (node)
	{
		if (value)
		{
			free(node->value);
			node->value = ft_strdup(value);
		}
	}
	else
	{
		if (value)
			add_back_env_node(&data->env,
				new_env_node(ft_strdup(name), ft_strdup(value)));
		else
			add_back_env_node(&data->env,
				new_env_node(ft_strdup(name), NULL));
	}
}

void	ft_export(t_data *data, t_exec *cmd)
{
	char	*name;
	char	*value;
	int		i;
	bool	append;

	i = 1;
	if (cmd->str[1] == NULL)
	{
		export0(data);
		g_exit_status =	0;
		return ;
	}
	while (cmd->str[i])
	{
		append = false;
		name = extract_name(cmd->str[i], &append);
		if (!name)
			return ;
		value = extract_value(cmd->str[i]);
		export1(data, name, value, append);
		free(name);
		free(value);
		i++;
	}
}
/***************************test section***********************************/
// t_env *env_to_linked_list(char **envp) {
//     t_env *head = NULL;
//     t_env *prev = NULL;
//     for (int i = 0; envp[i] != NULL; i++) {
//         char *name = strtok(envp[i], "=");
//         char *value = strtok(NULL, "=");
//         t_env *new_node = malloc(sizeof(t_env));
//         new_node->name = ft_strdup(name);
//         new_node->value = ft_strdup(value);
//         new_node->next = NULL;
//         if (prev == NULL) {
//             head = new_node;
//         } else {
//             prev->next = new_node;
//         }
//         prev = new_node;
//     }
//     return head;
// }
// void print_env(t_env *env) {
//     while (env != NULL) {
//         printf("%s=%s\n", env->name, env->value);
//         env = env->next;
//     }
// }
// void free_env(t_env *env) {
//     t_env *temp;
//     while (env != NULL) {
//         temp = env;
//         env = env->next;
//         free(temp->name);
//         free(temp->value);
//         free(temp);
//     }
// }
// void add_env(t_env **env, char *name, char *value) {
//     t_env *new_node = malloc(sizeof(t_env));
//     new_node->name = ft_strdup(name);
//     new_node->value = ft_strdup(value);
//     new_node->next = *env;
//     *env = new_node;
// }
// int main(int argc, char **argv, char **envp) {
//     t_exec new_node;
//     t_exec cmd ;
//     t_data data;
//     int status;
//     int i = 1;
//     data.envp_ = envp;
//     set_environment(&data);
//     cmd.str = malloc(sizeof(char *) * argc);  
//     new_node.str = malloc(sizeof(char *) * argc);  
//     while(argv[i])
//     {
//         cmd.str[i - 1] = argv[i];
//         i++;
//     }
//     cmd.str[i - 1] = NULL;
//     new_node.str[0] = ft_strdup("unset");
//     new_node.str[1] = ft_strdup("LESS");
//     new_node.str[2] = NULL;
// //     new_node->next = env;
//  //   env = new_node;")
//      //ft_export(&data, &cmd);
//     //printEnv(sort_environment(&data));
//    // printf("the value is **** of ZAK is  %s",getenv("ZAK"));
//    execute_command(&cmd, get_path(&cmd.str, &data, &status), &data);
//     //sort_environment(&data);
//      //ft_unset(&new_node, &data);
//      //print_env(sort_environment(&data));
// //     print_env(sort_environment(&data));
// //ft_unset(&new_node, &data);
// //print_env(data.env);
//     //print_env(env);
//     //cmd.str[1] = NULL;
//     //ft_export(&data, &cmd);

//     // free memory
//    // free_env(env);

//     return 0;
// }