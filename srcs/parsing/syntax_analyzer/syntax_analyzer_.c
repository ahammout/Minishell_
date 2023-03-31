/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:47 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/31 22:52:41 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    analyze_begin(t_data *data, t_tokens *token)
{
    char    c1;

    if (!data->err)
    {
        c1 = token->lex[0];
        if (c1 == AND || c1 == SEMICOLONE || c1 == PIPE)
            data->err = ft_strdup("Minishell: syntax error near unexpected token `newline'");
    }
}

void    analyze_end(t_data *data, t_tokens *token)
{
    char c1;

    if (!data->err)
    {
        c1 = token->lex[0];
        if (c1 == PIPE || c1 == AND || c1 == REDIN || c1 == REDOUT)
            data->err = ft_strdup("Minishell: syntax error near unexpected token `newline'");
    }
}

int is_metecharacter(int type)
{
    if (type == REDIN || type == REDOUT || type == APPEND \
        || type == HEREDOC || type == PIPE)
        return (1);
    return (0);
}