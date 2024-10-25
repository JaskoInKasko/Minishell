/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:28:50 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/13 22:28:52 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big_one, const char *small_one, size_t len)
{
	size_t	n;

	if (*small_one == 0)
		return ((char *)big_one);
	n = ft_strlen(small_one);
	while (*big_one && n <= len)
	{
		if (*big_one == *small_one && ft_strncmp(big_one, small_one, n) == 0)
			return ((char *)big_one);
		big_one++;
		len--;
	}
	return (NULL);
}
