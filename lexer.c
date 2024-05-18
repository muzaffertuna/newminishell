/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:18:39 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/06 01:15:50 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_new_token(char *value)
{
	t_token *new;
	new = (t_token *)malloc(sizeof(t_token));
	new->value = value;
	new->type = -1;
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
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}

void	ft_token_delimiter(t_token **token)
{
	t_token	*new;

	new = ft_new_token(NULL);
	ft_lst_token_append(token, new);
	(*token) = (*token)->next;
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

int		ft_tokenizer(char *line,t_token **head, int *index)
{
	if (ft_rule_one(line, head, index))
		return RULE_ONE;
	if (ft_rule_two(line, head, index))
			return RULE_TWO;
	if (ft_rule_three(line, head, index))
		return RULE_THREE;
	if (ft_rule_four(line, head, index))
		return RULE_FOUR;
	if (ft_rule_five(line, head, index))
		return RULE_FIVE;
	if (ft_rule_six(line, head, index))
		return RULE_SIX;
	if (ft_rule_seven(line, head, index))
		return RULE_SEVEN;
	if (ft_rule_eight(line, head, index))
		return RULE_EIGHT;
	if (ft_rule_nine(line, index))
		return RULE_NINE;
	if (ft_rule_ten(line, head, index))
		return RULE_TEN;
	return 0;
}
