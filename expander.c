/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:11:03 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/22 18:14:27 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_single_quote(char *str, int len)
{
	int	is_in_double_quotes;
	int	is_in_single_quotes;
	int	i;

	i = 0;
	is_in_double_quotes = 0;
	is_in_single_quotes = 0;
	while (i < len)
	{
		if (str[i] == '\"' && !is_in_single_quotes)
			is_in_double_quotes = !is_in_double_quotes;
		else if (str[i] == '\'' && !is_in_double_quotes)
			is_in_single_quotes = !is_in_single_quotes;
		i++;
	}
	if (is_in_single_quotes)
		return (1);
	return (0);
}

char	**ft_arr_append_free(char **arr, char *str)
{
	char	**aux;

	if (str == NULL)
		return (arr);
	aux = ft_arr_append(arr, str);
	free(str);
	return (aux);
}

int	ft_is_special_parameter(char ***arr, char *str, int *i, size_t *k)
{
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		*arr = ft_arr_append_free(*arr, ft_substr(str, *i, 2));
		*i += 1;
		*k = *i + 1;
		return (1);
	}
	return (0);
}

int	ft_in_double_quote(char *str, int len)
{
	int	is_in_double_quotes;
	int	is_in_single_quotes;
	int	i;

	i = 0;
	is_in_double_quotes = 0;
	is_in_single_quotes = 0;
	while (i < len)
	{
		if (str[i] == '\"' && !is_in_single_quotes)
			is_in_double_quotes = !is_in_double_quotes;
		else if (str[i] == '\'' && !is_in_double_quotes)
			is_in_single_quotes = !is_in_single_quotes;
		i++;
	}
	if (is_in_double_quotes)
		return (1);
	return (0);
}

int	ft_isname(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

size_t	ft_continue_if_name(char *str, int k)
{
	while (str[k] != 0x0 && ft_isname(str[k]) == 1)
		k++;
	if (ft_in_double_quote(str, k) == 0
		&& ft_in_double_quote(str, k - 1) == 1)
		k--;
	return (k);
}

void	ft_append_lst_str(char ***arr, char *str, int *i, size_t *k)
{
	size_t	a;

	a = *i;
	if (*k > a)
		*arr = ft_arr_append_free(*arr, ft_substr(str, a, *k - a));
	else if (*k < a)
		*arr = ft_arr_append_free(*arr, ft_substr(str, *k, a - *k));
}

char	**ft_brake_into_strings(char *str)
{
	int		i;
	size_t	k;
	char	**arr;

	i = -1;
	arr = 0;
	k = 0;
	while (str[++i])
	{
		if (str[i] == '$' && ft_in_single_quote(str, i) == 0)
		{
			arr = ft_arr_append_free(arr, ft_substr(str, k, i - k));
			k = i + 1;
			if (str[k] == 0x0)
				break ;
			if (ft_is_special_parameter(&arr, str, &i, &k) == 1)
				continue ;
			k = ft_continue_if_name(str, k);
			arr = ft_arr_append_free(arr, ft_substr(str, i, k - i));
			i = k - 1;
		}
	}
	ft_append_lst_str(&arr, str, &i, &k);
	return (arr);
}

char	*ft_getenv(t_env *envc, char *env_var)
{
	char	*str;

	str = NULL;

	if (envc == NULL || env_var == NULL)
		return (NULL);

	str = ft_strjoin(env_var, "=");
	while (envc)
	{
		if ((ft_strncmp(str, envc->key, ft_strlen(str)) == 0)
			&& ft_strlen(str) <= ft_strlen(envc->key))
		{
			free(str);
			return (envc->value);
		}
		envc = envc->next;
	}
	free(str);
	return (NULL);
}

void	ft_expand(char **aux, t_shell *shell)
{
	char	*str;
	size_t	i;

	i = 0;
	if (aux == NULL)
		return ;
	while (aux[i])
	{
		if (*aux[i] == '$' && *(aux[i] + 1) != 0x0)
		{
			if (*(aux[i] + 1) == '?')
				str = ft_itoa(0);
			else
			{
				str = ft_strdup(ft_getenv(shell->env, aux[i] + 1));
			}
			free(aux[i]);
			if (str != NULL)
				aux[i] = ft_strdup(str);
			else
				aux[i] = ft_strdup("");
			free(str);
		}
		i++;
	}
}

char	*ft_join_strings(char **aux)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ft_strdup("");
	if (aux != NULL)
	{
		while (aux[i] != NULL)
		{
			if (*aux[i] != 0x0)
				str = ft_strjoin_free(str, aux[i]);
			i++;
		}
	}
	ft_arr_free(aux);
	aux = 0;
	return (str);
}

void	ft_env_var_expand(t_args **args, t_shell *shell)
{
	char	**aux;
	t_args	*head;
	size_t	i;

	i = 0;
	head = *args;
	while (head)
	{
		i = 0;
		if (head->args)
		{
			while (head->args[i] != NULL)
			{
				if (ft_strchr(head->args[i], '$'))
				{
					aux = ft_brake_into_strings(head->args[i]);
					ft_expand(aux, shell);
					free(head->args[i]);
					head->args[i] = ft_join_strings(aux);
				}
				i++;
			}
		}
		head = head->next;
	}
}

void	ft_expander(t_shell *shell)
{
	t_args	*args;

	args = shell->parse;
	ft_env_var_expand(&args, shell);
	//ft_redir_expand(&args, shell);
	//ft_args_quote_removal(&args);
	//ft_pathname_expand(&args, shell);
	//ft_redir_quote_removal(&args);
}
