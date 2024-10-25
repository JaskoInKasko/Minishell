/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguliyev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:20:51 by iguliyev          #+#    #+#             */
/*   Updated: 2023/09/13 22:20:53 by iguliyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha (c) || ft_isdigit (c))
		return (1);
	return (0);
}
/*#include <stdio.h>

int main ()
{
    printf ("%d", ft_isalnum('a'));
    return (0);
}*/
