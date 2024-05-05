/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:18:39 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/05 20:45:29 by mtoktas          ###   ########.fr       */
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
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}

void	ft_token_delimiter(t_token **token)
{
	t_token	*new;

	new = ft_new_token(NULL, 0);
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
	if (ft_rule_one(line, head, index) == RULE_ONE)
		return RULE_ONE;
	else if(ft_rule_two(line, head, index) == RULE_TWO)
		return RULE_TWO;
	else if(ft_rule_three(line, head, index) == RULE_THREE)
		return RULE_THREE;
	else if(ft_rule_four(line, head, index) == RULE_FOUR)
		return RULE_FOUR;
	else if(ft_rule_five(line, head, index) == RULE_FIVE)
		return RULE_FIVE;
	else if(ft_rule_six(line, head, index) == RULE_SIX)
		return RULE_SIX;
	else if(ft_rule_seven(line, head, index) == RULE_SEVEN)
		return RULE_SEVEN;
	else if(ft_rule_eight(line, head, index) == RULE_EIGHT)
		return RULE_EIGHT;
	else if(ft_rule_nine(line, index) == RULE_NINE)
		return RULE_NINE;
	else if(ft_rule_ten(line, head, index) == RULE_TEN)
		return RULE_TEN;
	return 0;
}

