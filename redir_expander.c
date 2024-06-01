/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:25:32 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/31 16:49:50 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_expand(t_args **args, t_shell *shell)
{
	char	**aux;
	t_redir	*head_redir;
	t_args	*head;

	head = *args;
	while (head)
	{
		head_redir = (*args)->redir;
		while (head_redir)
		{
			if (ft_strchr(head_redir->operand, '$'))
			{
				aux = ft_brake_into_strings(head_redir->operand);
				ft_expand(aux, shell);
				free(head_redir->operand);
				head_redir->operand = ft_join_strings(aux);
			}
			head_redir = head_redir->next;
		}
		head = head->next;
	}
}

