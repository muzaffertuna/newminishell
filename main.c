/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:37:27 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/04 16:53:30 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *get_LOGNAME(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "LOGNAME=", 8) == 0)
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
	printf("line : %s\n", line);

	t_token *head;
	t_token *token = ft_new_token(NULL, 0);
	head = token;

	int index = 0;
	while(line[index] != '\0')
	{
		ft_tokenizer(line, &head, index);
		index++;
	}
	t_token *tmp;
	tmp = head;
	while (tmp)
	{
		printf("value : %s\n", tmp->value);
		tmp = tmp->next;
	}
}
