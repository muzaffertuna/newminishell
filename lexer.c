/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:18:39 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/04 17:11:12 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_new_token(char *value, int type)
{
	t_token *new;
	new = (t_token *)malloc(sizeof(t_token));
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_lst_token_append(t_token **head, t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	if (!head)
	{
		*head = token;
		return ;
	}
	tmp = ft_get_last_token(head);
	tmp->next = token;
}

void	ft_token_delimiter(t_token **token)
{
	t_token	*new;

	new = ft_new_token(NULL, 0);
	ft_lst_token_append(token, new);
}

t_token		*ft_get_last_token(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

char	*ft_append_char(char *str, char c)
{
	char	*new_str;
	size_t	i;

	i = -1;
	if (!str)
		str = ft_strdup("");
	new_str = malloc(ft_strlen(str) + 2);
	while (++i < ft_strlen(str))
		new_str[i] = str[i];
	new_str[i] = c;
	new_str[++i] = '\0';
	free(str);
	return (new_str);
}


void	ft_tokenizer(char *line,t_token **head, int index)
{
	t_token *last_token;

	if(line[index] == ' ')
	{
		ft_token_delimiter(head);
	}
	else
	{
		last_token = ft_get_last_token(head);
		(last_token)->value = ft_append_char((last_token)->value, line[index]);
	}
}

