/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:29:16 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/13 22:29:18 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c - 'A' + 'a';
	return (c);
}
/*#include<stdio.h>
#include <ctype.h>

int main()
{
    char ch = 'H';

    printf("%c\n", tolower(ch));
    printf("%c\n", ft_tolower(ch));
}*/
