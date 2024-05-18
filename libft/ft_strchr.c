/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:21:17 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/05 23:50:28 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strchr(const char *s, int c)
{
	while ((*s != (char)c) && (*s != 0x0))
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
