/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:37:24 by mtoktas           #+#    #+#             */
/*   Updated: 2024/06/09 01:21:47 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
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
	GREATER = 1,
	LESS,
	DGREATER,
	HEREDOC
};

typedef struct s_token
{
	enum e_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	char 	*operator;
	char	*operand;
	enum e_redir	type;
	struct s_redir	*next;
} t_redir;

typedef struct s_args
{
	char **args;
	char *cmd;
	struct s_args *next;
	t_redir *redir;
	t_redir *first_redir;
	int is_pipe;
} t_args;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_args *parse;
	t_token *token;
	t_env *env;
} t_shell;



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

//--------------------------main.c--------------------------
char *get_LOGNAME(char **envp);

//--------------------------env.c--------------------------
void print_env(char **envp);
void add_env_last(t_env **env_last);
t_env *new_env();
void init_env(t_env **env_last, char *key, char *value);
void load_enviroment(t_env **first, char **envp);

//-----------------------------parser.c--------------------------
int	ft_ispipe(t_token *token);
int	ft_isredir(t_token *token);
void	ft_arr_free(char **arr);
int	ft_arr_len(char **arr);
char	**ft_arr_append(char **arr, char *str);
t_args	*ft_new_args(char *arg);
void	ft_parse_pipe(t_args **args_head, t_shell *shell);
void	ft_parser(t_shell *shell);

//-----------------------------parse_redirection.c--------------------------
t_redir	*ft_new_redir(char *content);
t_redir	*ft_lst_redir_last(t_redir *head);
void	ft_redir_delimiter(t_redir **redir, t_args **args_head);
int	ft_check_redir(char *redir_op);
int	ft_has_redir(t_token *token);
void ft_parse_redir(t_token **t_head, t_args **args_head);


//-----------------------------expander.c-----------------------------
int	ft_in_single_quote(char *str, int len);
char	**ft_arr_append_free(char **arr, char *str);
int	ft_is_special_parameter(char ***arr, char *str, int *i, size_t *k);
int	ft_in_double_quote(char *str, int len);
int	ft_isname(int c);
size_t	ft_continue_if_name(char *str, int k);
void	ft_append_lst_str(char ***arr, char *str, int *i, size_t *k);
char	**ft_brake_into_strings(char *str);
char	*ft_getenv(t_env *envc, char *env_var);
void	ft_expand(char **aux, t_shell *shell);
char	*ft_join_strings(char **aux);
void	ft_env_var_expand(t_args **args, t_shell *shell);
void	ft_expander(t_shell *shell);


//--------------------------------redir_expander.c------------------------------------------//
void	ft_redir_expand(t_args **args, t_shell *shell);

//--------------------------------quote_expander.c------------------------------------------//
char	**ft_append_if_diff(char **arr, char *str, size_t *i, size_t *k);
char	**ft_quote_removal(char *str, char **arr, int is_on_quote);
void	ft_args_quote_removal(t_args **args);

//---------------------------pathname_expander.c--------------------------
int	ft_which_builtin(t_args *args);
int ft_contain_slash(char *str);
void	ft_find_path(char **path, char *cmd, t_args *args);
int	ft_is_path_xok(char *str);
void	ft_check_abs_path(char *str);
int	ft_search_expand_path(char **arr, char *str, t_shell *shell, t_args *head);
void	ft_pathname_expand(t_args **args, t_shell *shell);

//---------------------------redir_quote_removal.c--------------------------
void	ft_redir_quote_removal(t_args **args);

#endif
