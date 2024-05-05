/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:37:24 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/06 01:05:17 by mtoktas          ###   ########.fr       */
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
# include <sys/ioctl.h>
# include "libft/libft.h"

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

enum e_token_type{
	OPERATOR_T,
	WORD_T,
};

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
	enum e_token_type	type;
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
//--------------------------lexer.c--------------------------
t_token *ft_new_token(char *value);
void	ft_token_delimiter(t_token **token);
char	*ft_append_char(char *str, char c);
int		ft_tokenizer(char *line,t_token **head, int *index);

//--------------------------rules.c--------------------------
int ft_rule_one(char *line, t_token **head, int *index);
int ft_is_quoted(char *line, int index);
int ft_rule_two(char *line, t_token **head, int *index);
int ft_rule_three(char *line, t_token **head, int *index);
char	*ft_strjoin_free(char *str1, char *str2);
int ft_rule_four(char *line, t_token **head, int *index);
void	ft_substitution_control(char *line, t_token **head, int *index);
int ft_rule_five(char *line, t_token **head, int *index);
int ft_rule_six(char *line, t_token **head, int *index);
int ft_rule_seven(char *line, t_token **head, int *index);
int ft_rule_eight(char *line, t_token **head, int *index);
int ft_rule_nine(char *line, int *index);
int ft_rule_ten(char *line, t_token **head, int *index);
#endif

