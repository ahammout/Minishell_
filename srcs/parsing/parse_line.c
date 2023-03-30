/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:04:41 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/30 21:58:32 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

////////////////////////////////// PARSE_LINE //////////////////////////////

t_exec  *parse_line(t_data *data)
{
    if (lexer(data))
    {
        if (syntax_analyzer(data) && !data->err)
        {
            if (expander(data) && !data->err)
            {
                // display_tokens(data->tokens);
                return (parser(data));
            }
        }
    }
    return (0);
}