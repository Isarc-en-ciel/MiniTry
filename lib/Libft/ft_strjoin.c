/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:38:14 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/27 12:48:46 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy_cat(char *dst, char *src, char *src2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (src2[j] != '\0')
	{
		dst[i] = src2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_free_str(char *s1, char *s2, char flag)
{
	if (flag == '1')
		free(s1);
	else if (flag == '2')
		free(s2);
	else if (flag == '3')
	{
		free(s1);
		free(s2);
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2, char flag)
{
	size_t	n;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen(s1) + ft_strlen(s2);
	if (n == 0)
	{
		ft_free_str(s1, s2, flag);
		return (ft_calloc(1, 1));
	}
	strjoin = (char *) malloc(sizeof(char) * (n + 1));
	if (!strjoin)
		return (ft_free_str(s1, s2, flag));
	strjoin = ft_strcpy_cat(strjoin, (char *)s1, (char *)s2);
	ft_free_str(s1, s2, flag);
	return (strjoin);
}
