/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:11:52 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/31 18:14:21 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_append_if_diff(char **arr, char *str, size_t *i, size_t *k)
{
	if (*i != *k)
	{
		arr = ft_arr_append_free(arr, ft_substr(str, *k, *i - *k));
		*k = *i;
	}
	return (arr);
}

char	**ft_quote_removal(char *str, char **arr, int is_on_quote)
{
	size_t	i;
	size_t	k;
	char	quote;

	i = 0;
	k = 0;
	while (str[i] != 0x0)
	{
		if (is_on_quote == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			is_on_quote = !is_on_quote;
			arr = ft_append_if_diff(arr, str, &i, &k);
		}
		else if (is_on_quote == 1 && str[i] == quote)
		{
			arr = ft_arr_append_free(arr, ft_substr(str, k + 1, i - k - 1));
			is_on_quote = !is_on_quote;
			k = i + 1;
		}
		i++;
	}
	arr = ft_append_if_diff(arr, str, &i, &k);
	return (arr);
}


void	ft_args_quote_removal(t_args **args)
{
	t_args	*head;
	char	**arr;
	size_t	i;
	int		is_on_quote;

	head = *args;
	is_on_quote = 0;
	while (head)
	{
		i = 0;
		if (head->args)
		{
			while (head->args[i])
			{
				arr = 0;
				arr = ft_quote_removal(head->args[i], arr, is_on_quote);
				free(head->args[i]);
				head->args[i] = ft_join_strings(arr);
				i++;
			}
		}
		head = head->next;
	}
}
