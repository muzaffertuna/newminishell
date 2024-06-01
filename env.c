/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkilitci <kkilitci@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:22:33 by mtoktas           #+#    #+#             */
/*   Updated: 2024/06/01 20:41:45 by kkilitci         ###   ########.fr       */
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
	int temp_index;
	t_env *env_last;
	//t_env *env_last1;
	
	env_last = *first;
	temp_index = 0;
	//env_last1 = env_last;
	//printf("-------------------*******%s\n",ft_substr(envp[0, 0, ft_strchr(envp[0], '=') - envp[0]));
	temp_index =  ft_strchr(envp[0], '=') - envp[0];
    init_env(first, ft_strdup(ft_substr(envp[0], 0,temp_index)), ft_strdup(ft_substr(envp[0], temp_index + 1, ft_strlen(envp[0]) - temp_index - 1)));

	while (envp[i])
	{
		add_env_last(&env_last);
		temp_index = ft_strchr(envp[i], '=') - envp[i];
		init_env(&env_last, ft_strdup(ft_substr(envp[i], 0, temp_index)), ft_strdup(ft_substr(envp[i], temp_index + 1, ft_strlen(envp[i]) - temp_index - 1)));
		i++;
	}
	// printf("*************\n");
	// for (size_t i = 0; i < 5; i++)
	// {
	// 	printf("%s", (*first)->key);
	// 	printf("%s \n", (*first)->value);
	// 	printf("%s\n", envp[i]);
	// 	printf("*************\n");
	// 	(*first) = (*first)->next;
	// }
	
}
