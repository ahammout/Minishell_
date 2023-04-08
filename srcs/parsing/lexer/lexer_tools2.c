/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:26:46 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/08 21:41:12 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	quotes_size(char *lexem, char type)
{
	int	s;
	int	q;

	s = 0;
	q = 0;
	while (lexem[s])
	{
		if (lexem[s] == type)
			q++;
		s++;
		if (q == 2)
			break ;
	}
	return (s);
}

int	expand_size(char *lexem)
{
	int	s;

	s = 0;
	while (lexem[s] == EXPAND_ || lexem[s] == '@' \
		|| lexem[s] == '*')
		s++;
	while (ft_isalpha(lexem[s]) || ft_isdigit(lexem[s]) \
		|| lexem[s] == '_' || lexem[s] == '?')
		s++;
	return (s);
}
