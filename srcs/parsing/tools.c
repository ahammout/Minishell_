/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 03:30:30 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/08 16:11:53 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	generate_error(t_data *data)
{
	g_exit_status = 2;
	ft_putstr_fd(data->err, 2);
	ft_putstr_fd("\n", 2);
}

char	*ft_strdup_free(char *s1)
{
	int		i;
	char	*s2;

	if (!s1)
		return (NULL);
	i = 0;
	s2 = (char *) malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!s2)
		return (0);
	while (s1[i])
	{
		s2[i] = s1[i];
		i ++;
	}
	free(s1);
	s2[i] = '\0';
	return (s2);
}

int	white_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]))
			return (1);
		i++;
	}
	return (0);
}
