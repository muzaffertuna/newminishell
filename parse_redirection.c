/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:44:23 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/21 17:19:42 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_new_redir(char *content)
{
	t_redir	*new;

	(void)content;
	new = malloc(sizeof(t_redir));
	new->next = NULL;
	new->operand = NULL;
	new->operand = NULL;
	return (new);
}

// t_redir	*ft_lst_redir_last(t_redir *head)
// {
// 	t_redir	*tmp;

// 	if (head == NULL)
// 		return (NULL);
// 	tmp = head;
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;
// 	return (tmp);
// }

// void	ft_lst_redir_append(t_redir **head, t_redir *token)
// {
// 	t_redir	*tmp;

// 	if (!token)
// 		return ;
// 	if (!head)
// 	{
// 		*head = token;
// 		return ;
// 	}
// 	tmp = *head;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = token;
// }

void	ft_redir_delimiter(t_redir **redir, t_args **args_head)
{
	t_redir	*new;

	new = ft_new_redir(NULL);
	if ((*args_head)->first_redir == NULL)
	{
		(*args_head)->redir = new;
		(*args_head)->first_redir = new;
		return ;
	}
	(*redir)->next = new;        //ft_lst_redir_append
	*redir = (*redir)->next;
}

int	ft_check_redir(char *redir_op)
{
	const char	*op;

	op = (const char *)redir_op;
	if ((ft_strncmp("<", op, ft_strlen(op)) == 0) && ft_strlen(op) == 1)
		return (1);
	if ((ft_strncmp(">", op, ft_strlen(op)) == 0) && ft_strlen(op) == 1)
		return (1);
	if ((ft_strncmp("<<", op, ft_strlen(op)) == 0) && ft_strlen(op) == 2)
		return (1);
	if ((ft_strncmp(">>", op, ft_strlen(op)) == 0) && ft_strlen(op) == 2)
		return (1);
	return (0);
}

int	ft_has_redir(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (ft_check_redir(tmp->value) == 1)
			return (1);
		if (tmp->type == OPERATOR_T)
			return (0);
		tmp = tmp->next;
	}
	return (0);
}

void ft_parse_redir(t_token **t_head, t_args **args_head)
{
	if ((*args_head)->redir == NULL)
	{
		(*args_head)->redir = ft_new_redir(NULL);
		(*args_head)->first_redir = (*args_head)->redir;
	}

	(*args_head)->redir->operator = ft_strdup((*t_head)->value);
	if ((*t_head)->next != NULL)
	{
		*t_head = (*t_head)->next;
		(*args_head)->redir->operand = ft_strdup((*t_head)->value);
		if (ft_has_redir(*t_head) == 1)
		{
			ft_redir_delimiter(&(*args_head)->redir, args_head);
		}
	}
}
