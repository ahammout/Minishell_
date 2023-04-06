/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:47 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/05 22:46:17 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    analyze_begin(t_data *data, t_tokens *token)
{
    if (!data->err)
    {
        if (token->lex[0] == AND || token->lex[0] == SEMICOLONE || token->lex[0] == PIPE)
            data->err = ft_strdup("Minishell: syntax error near unexpected token `newline'");
    }
}

void    analyze_end(t_data *data, t_tokens *token)
{
    if (!data->err)
    {
        if (token->lex[0] == PIPE || token->lex[0] == AND || token->lex[0] == REDIN || token->lex[0] == REDOUT)
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