/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:19:49 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/31 22:59:49 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*word;
	size_t	i;
	size_t	ls1;
	size_t	ls2;

	if (!s1 || !s2)
		return (0);
	i = 0;
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	word = (char *) malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!word)
		return (0);
	ft_memcpy(word, s1, ls1);
	while (s2[i] && i < ls2)
	{
		word[ls1 + i] = s2[i];
		i++;
	}
	word[ls1 + i] = '\0';
	return (word);
}
