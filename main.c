/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:37:27 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/06 01:27:05 by mtoktas          ###   ########.fr       */
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

void print_env(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}



int main(int ac, char **av, char **envp)
{
	// print_env(envp);
	(void) ac;
	(void) av;
	char *line = readline(get_LOGNAME(envp));

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
		printf("Tokens : %s\n", tmp->value);
		tmp = tmp->next;
	}
}
