/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:22:33 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/22 18:07:37 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void add_env_last(t_env **env_last)
{
	t_env *new;
	new = new_env();
	(*env_last)->next = new;
	(*env_last) = new;
}

t_env *new_env()
{
	t_env *env;
	env = malloc(sizeof(env));
	env->next = NULL;
	env->key = NULL;
	env->value = NULL;
	return (env);
}

void init_env(t_env **env_last, char *key, char *value)
{
	(*env_last)->key = ft_strjoin_free(key, "=");
	(*env_last)->value = value;
}

void load_enviroment(t_env **first, char **envp)
{
	int i = 1;
	t_env *env_last;
	env_last = *first;
	//printf("-------------------*******%s\n",ft_substr(envp[0, 0, ft_strchr(envp[0], '=') - envp[0]));
    init_env(first, ft_strdup(ft_substr(envp[0], 0, ft_strchr(envp[0], '=') - envp[0])), ft_strdup(ft_strchr(envp[0], '=') + 1));

	while (envp[i])
	{
    add_env_last(&env_last);
    init_env(&env_last, ft_strdup(ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i])), ft_strdup(ft_strchr(envp[i], '=') + 1));
    i++;
	}
}
