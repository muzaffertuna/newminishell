/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:37:27 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/18 15:08:20 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *get_LOGNAME(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "LOGNAME=", 8) == 0)
			return (ft_strjoin(envp[i] + 8, "$>"));
		i++;
	}
	return (NULL);
}



int main(int ac, char **av, char **envp)
{
	// print_env(envp);
	(void) ac;
	(void) av;
	char *line = readline(get_LOGNAME(envp));
	print_env(envp);

	t_token *head;
	t_token *token = ft_new_token(NULL);
	head = token;

	int index = 0;

	while (index < (int)ft_strlen(line))
	{
		ft_tokenizer(line, &head, &index);
	}
	t_token *tmp;
	tmp = token;
	while (tmp)
	{
		printf("Tokens : %s       ", tmp->value);
		printf(" =>  token type : %d\n", tmp->type);
		tmp = tmp->next;
	}
}
/*
int main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	print_env(envp);
	printf("---------------------\n");
	printf("---------------------\n");
	printf("---------------------\n");
	printf("---------------------\n");
	printf("---------------------\n");
	t_env *env_first = new_env();
	load_enviroment(&env_first, envp);

	t_env *tmp;
	tmp = env_first;
	while (tmp)
	{
		if (tmp->next == (void *)0x5f)
			break;
		printf("key : %s\n", tmp->key);
		printf("value : %s\n", tmp->value);
		tmp = tmp->next;
	}
	return (0);
}*/
