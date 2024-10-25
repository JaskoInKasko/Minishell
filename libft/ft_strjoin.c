/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:27:25 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/13 22:27:27 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*m;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	m = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (m == NULL)
		return (NULL);
	while (s1[i])
	{
		m[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		m[j] = s2[i];
		i++;
		j++;
	}
	m[j] = '\0';
	return (m);
}
/*#include <stdio.h>

int main ()
{
    char a[] = "abc";
    char b[] = "qwe";

    printf("%s", ft_strjoin(a, b));
    return (0);

}*/
