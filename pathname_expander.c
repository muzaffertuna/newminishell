/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:34:43 by mtoktas           #+#    #+#             */
/*   Updated: 2024/06/09 01:21:45 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_which_builtin(t_args *args)
{
	size_t	len;

	len = ft_strlen(args->args[0]);
	if ((ft_strncmp(args->args[0], "echo", 4) == 0) && (len == 4))
		return (1);
	else if ((ft_strncmp(args->args[0], "cd", 2) == 0) && (len == 2))
		return (2);
	else if ((ft_strncmp(args->args[0], "pwd", 3) == 0) && (len == 3))
		return (3);
	else if ((ft_strncmp(args->args[0], "export", 6) == 0) && (len == 6))
		return (4);
	else if ((ft_strncmp(args->args[0], "unset", 5) == 0) && (len == 5))
		return (5);
	else if ((ft_strncmp(args->args[0], "env", 3) == 0) && (len == 3))
		return (6);
	else if ((ft_strncmp(args->args[0], "exit", 4) == 0) && (len == 4))
		return (7);
	return (-1);
}


int	ft_contain_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	ft_find_path(char **path, char *cmd, t_args *args)
{
	char	*new_path;
	size_t	i;

	i = 0;
	if (path != NULL)
	{
		while (path[i])
		{
			new_path = ft_strjoin(path[i], "/");
			new_path = ft_strjoin_free(new_path, cmd);
			if (access(new_path, X_OK) == 0)
			{
				free(args->args[0]);
				args->args[0] = new_path;
				args->cmd = args->args[0];
				break ;
			}
			free(new_path);
			i++;
		}
		ft_arr_free(path);
	}
}

int	ft_is_path_xok(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (dir != NULL)
	{
		printf("command not found");
		closedir(dir);
		exit(126);
		return (1);
	}
	if (access(str, X_OK) == -1)
	{
		printf("command not found");
		exit(126);
		return (1);
	}
	return (0);
}

void	ft_check_abs_path(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (dir != NULL)
	{
		printf("is a directory\n");
		closedir(dir);
		exit(126);
	}
	else if (access(str, F_OK) == -1)
	{
		printf("No such file or directory\n");
		exit(127);
	}
	else if (access(str, X_OK) == -1)
	{
		printf("Permission Denied\n");
		exit(127);
	}
}

int	ft_search_expand_path(char **arr, char *str, t_shell *shell, t_args *head)
{
	arr = ft_split(ft_getenv(shell->env, "PATH"), ':');
	ft_find_path(arr, str, head);
	if (ft_is_path_xok(head->args[0]) == 1)
	{
		free(str);
		return (1);
	}
	return (0);
}

void	ft_pathname_expand(t_args **args, t_shell *shell)
{
	t_args	*head;
	char	*str;
	char	**arr;

	arr = NULL;
	head = *args;
	str = NULL;
	while (head)
	{
		if (head->args)
		{
			if (ft_which_builtin(head) == -1)
			{
				str = ft_strdup(head->args[0]);
				if (ft_contain_slash(str) == 1)
					ft_check_abs_path(str);
				else
					if (ft_search_expand_path(arr, str, shell, head) == 1)
						break ;
				free(str);
			}
		}
		head = head->next;
	}
}
