/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_quote_removal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:08:13 by mtoktas           #+#    #+#             */
/*   Updated: 2024/06/09 01:21:37 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_quote_removal(t_args **args)
{
	t_args	*head;
	t_redir	*redir_head;
	char	**arr;
	int		is_on_quote;

	head = *args;
	is_on_quote = 0;
	while (head)
	{
		redir_head = head->redir;
		while (redir_head)
		{
			arr = 0;
			arr = ft_quote_removal(redir_head->operand, arr, is_on_quote);
			free(redir_head->operand);
			redir_head->operand = ft_join_strings(arr);
			redir_head = redir_head->next;
		}
		head = head->next;
	}
}
