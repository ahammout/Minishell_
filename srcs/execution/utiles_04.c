/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_04.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 06:43:28 by zessadqu          #+#    #+#             */
/*   Updated: 2023/04/06 06:43:55 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr_free1(char *s1, int start, int end)
{
	char	*str;

	if (!s1)
		return (NULL);
	else
	{
		str = ft_substr(s1, start, end);
		free(s1);
		return (str);
	}
}