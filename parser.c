/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:04:04 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/21 17:19:37 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ispipe(t_token *token)
{
	if (token->type == OPERATOR_T && ft_strncmp(token->value, "|", 2) == 0)
		return (1);
	return (0);
}

int	ft_isredir(t_token *token)
{
	if (token->type == OPERATOR_T && (ft_strncmp(token->value, ">", 2) == 0 || ft_strncmp(token->value, "<", 2) == 0))
		return (1);
	return (0);
}

void	ft_arr_free(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
	arr = 0;
}

int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

char	**ft_arr_append(char **arr, char *str)
{
	char	**new_arr;
	int		i;
	int		arr_len;

	if (arr == NULL)
	{
		arr = malloc(sizeof(char *) * 2);
		arr[0] = ft_strdup(str);
		arr[1] = NULL;
		return (arr);
	}
	arr_len = ft_arr_len(arr);
	new_arr = malloc((arr_len + 2) * sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < arr_len)
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	ft_arr_free(arr);
	return (new_arr);
}

t_args	*ft_new_args(char *arg)
{
	t_args	*new_args;

	new_args = malloc(sizeof(t_args));
	if (!new_args)
		return (NULL);
	new_args->args = NULL;
	new_args->cmd = arg;
	new_args->next = NULL;
	new_args->redir = NULL;
	new_args->first_redir = NULL;
	new_args->is_pipe = 0;
	return (new_args);
}

void	ft_parse_pipe(t_args **args_head, t_shell *shell)
{
	t_args	*new_args;

	shell->parse->is_pipe = 1;
	new_args = ft_new_args(NULL);
	(*args_head)->next = new_args;
	(*args_head) = new_args;
}


void	ft_parser(t_shell *shell)
{
	t_token	*t_head;
	t_args	*args_head;

	t_head = shell->token;
	shell->parse = ft_new_args(NULL);
	args_head = shell->parse;

	while (t_head)
	{
		if (t_head->type == WORD_T)
		{
			args_head->args = ft_arr_append(args_head->args, t_head->value);
		}
		else if (ft_ispipe(t_head) == 1)
			ft_parse_pipe(&args_head, shell);
		else
		{
			ft_parse_redir(&t_head, &args_head);
		}
		t_head = t_head->next;
	}
}
