/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:37:27 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/31 16:49:45 by mtoktas          ###   ########.fr       */
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

/*
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
}*/
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




// int main(int ac, char **av, char **envp)
// {
// 	(void) ac;
// 	(void) av;

// 	char *line = readline(get_LOGNAME(envp));


// 	// create env struct then load and print env
// 	// t_env *env_first = new_env();
// 	// load_enviroment(&env_first, envp);
// 	// print_env(envp);


// 	// create token for Tokenizer
// 	t_token *token = ft_new_token(NULL);


// 	// create shell struct
// 	t_shell *shell = malloc(sizeof(t_shell));
// 	//shell->env = env_first;
// 	shell->token = token;
// 	shell->parse = NULL;

// 	int index = 0;

// 	while (index < (int)ft_strlen(line))
// 	{
// 		ft_tokenizer(line, &token, &index);
// 	}


// 	// Print Tokenizer
// 	// t_token *tmp;
// 	// tmp = shell->token;
// 	// while (tmp)
// 	// {
// 	// 	printf("Tokens : %s       ", tmp->value);
// 	// 	printf(" =>  token type : %d\n", tmp->type);
// 	// 	tmp = tmp->next;
// 	// }


// 	// Print Parser with struct values
// 	ft_parser(shell);
// 	t_args *tmp_args;
// 	t_redir *tmp_redir;
// 	tmp_args = shell->parse;
// 	int j = 0;
// 	while (tmp_args)
// 	{
// 		int i = 0;
// 		while (tmp_args->args[i])
// 		{
// 			printf("[%d]Args : %s       ",j, tmp_args->args[i]);
// 			i++;
// 		}
// 		tmp_redir = tmp_args->first_redir;
// 		printf(" \n\n\n");
// 		while (tmp_redir)
// 		{
// 			printf(" =>  operator : %s\n", tmp_redir->operator);
// 			printf(" =>  operand : %s\n", tmp_redir->operand);
// 			tmp_redir = tmp_redir->next;
// 		}
// 		printf(" =>  is_pipe : %d\n\n\n", tmp_args->is_pipe);
// 		j++;
// 		tmp_args = tmp_args->next;
// 	}
// 	return (0);
// }


void handle_signal(int sig)
{
    if (sig == SIGINT)
    {
        printf("\nCtrl+C pressed, exiting...\n");
        exit(0);
    }
    else if (sig == SIGQUIT)
    {
        printf("\nCtrl+\\ pressed, exiting...\n");
        exit(0);
    }
    // Diğer sinyaller için gerekli işlemler eklenebilir.
}

void init_signal(void)
{
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);
    // Diğer sinyaller için gerekli işlemler burada eklenebilir.
}

int main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	init_signal();
    using_history();
	t_env *env_first = new_env();
	load_enviroment(&env_first, envp);

	while(1)
	{

	char *line = readline(get_LOGNAME(envp));
	add_history(line);
	t_token *token = ft_new_token(NULL);


	t_shell *shell = malloc(sizeof(t_shell));
	shell->token = token;
	shell->parse = NULL;
	shell->env = env_first;
	int index = 0;
	while (index < (int)ft_strlen(line))
	{
		ft_tokenizer(line, &token, &index);
	}

	ft_parser(shell);
	ft_expander(shell);
	t_args *tmp_args;
	t_redir *tmp_redir;
	tmp_args = shell->parse;
	int j = 0;
	while (tmp_args)
	{
		int i = 0;
		while (tmp_args->args[i])
		{
			printf("[%d]Args : %s       ",j, tmp_args->args[i]);
			i++;
		}
		tmp_redir = tmp_args->first_redir;
		printf(" \n\n");
		while (tmp_redir)
		{
			printf(" =>  operator : %s\n", tmp_redir->operator);
			printf(" =>  operand : %s\n", tmp_redir->operand);
			tmp_redir = tmp_redir->next;
		}
		printf(" =>  is_pipe : %d\n\n\n", tmp_args->is_pipe);
		j++;
		tmp_args = tmp_args->next;
	}
	free(line);
	HISTORY_STATE *history_state = history_get_history_state();
	history_set_history_state(history_state);
    free(history_state);
	}
	return (0);
}
