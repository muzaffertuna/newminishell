/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:37:24 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/04 17:11:30 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

# define RULE_ONE 	1
# define RULE_TWO 	2
# define RULE_THREE	3
# define RULE_FOUR 	4
# define RULE_FIVE 	5
# define RULE_SIX 	6
# define RULE_SEVEN 7
# define RULE_EIGHT	8
# define RULE_NINE 	9
# define RULE_TEN	10


enum e_builtin
{
	EXIT,
	CD,
	PWD,
	ECHO,
	EXPORT,
	UNSET,
	ENV,
};

enum e_redir
{
	NO_REDIR,
	REDIR_OUT,
	REDIR_IN,
	REDIR_APPEND,
};

enum	e_token
{
	WORD,
	PIPE,
	SEMICOLON,
	REDIR,
};

typedef struct s_token
{
	enum e_token	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/*typedef struct s_cmd
{
	char			**argv;
	enum e_builtin	builtin;
	enum e_redir	redir;
	char			*redir_file;
}	t_cmd;*/

/*typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;*/

/*typedef struct s_data
{
	t_env	*env;
	t_cmd	*cmd;
}	t_data;*/

//--------------------------libft.c--------------------------
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_tokenizer(char *line,t_token **head, int index);
t_token *ft_new_token(char *value, int type);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_append_char(char *str, char c);
t_token		*ft_get_last_token(t_token **head);
#endif

