/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoktas <mtoktas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:01:41 by mtoktas           #+#    #+#             */
/*   Updated: 2024/05/06 01:27:44 by mtoktas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_rule_one(char *line, t_token **head, int *index)
{
	if(line[*index] == '\0')
	{
		if((*head)->value == NULL)
		{
			ft_append_char((*head)->value, line[*index]);
			return 1;
		}
	}
	return 0;
}

int ft_is_quoted(char *line, int index)
{
    char quote_type;
    int flag = 0;
    int i = 0;
    while (i <= index)
    {
        if((line[i] == '\"' || line[i] == '\'') && flag == 0)
        {
            quote_type = line[i];
            flag = 1;
        }
        else if((line[i] == '\"' || line[i] == '\'') && flag == 1 && line[i] == quote_type)
        {
            quote_type = '\0';
            flag = 0;
        }
        i++;
    }
    return flag;
}

int ft_rule_two(char *line, t_token **head, int *index)
{
    if(ft_strchr("><", line[*index]) && !ft_is_quoted(line, *index) && (*head)->type == OPERATOR_T && ft_strlen((*head)->value) == 1 && (*index) != 0)
    {
        if(line[*index - 1] == line[*index])
        {
            (*head)->value = ft_append_char((*head)->value, line[*index]);
            (*index)++;
            return 1;
        }
    }
    return 0;
}

int ft_rule_three(char *line, t_token **head, int *index)
{
    if(((*head)->type == OPERATOR_T) && (!ft_strchr(">|<", line[*index])) && (*index) != 0)
    {
        ft_token_delimiter(head);
        return 1;
    }
    return 0;
}
char	*ft_strjoin_free(char *str1, char *str2)
{
	char	*tmp;

	if (str1 == NULL)
		str1 = ft_strdup("");
	tmp = ft_strjoin(str1, str2);
	free(str1);
	str1 = tmp;
	return (str1);
}
int ft_rule_four(char *line, t_token **head, int *index)
{
    int tmp; 
    char *str;
    char quote_type;
    
    if(line[*index] == '\"' || line[*index] == '\'')
    {
        quote_type = line[*index];
        tmp = *index + 1;
        while(line[tmp])
        {
            if(line[tmp] == quote_type)
            {
                str = ft_substr(line, *index, tmp - *index + 1);
                (*head)->value = ft_strjoin_free((*head)->value, str);
                free(str);
				(*head)->type = WORD_T;
				*index = tmp + 1;
                return 1;
            }
            tmp++;
        }
    }
    return 0;
}

void	ft_substitution_control(char *line, t_token **head, int *index)
{
    (void)head;
	if (line[*index] == '`')
	{
		return ;
	}
	if (ft_strncmp(line + *index, "${", 2) == 0)
	{
		return ;

	}
	if (ft_strncmp(line + *index, "$((", 3) == 0)
	{
		return ;

	}
	else if (ft_strncmp(line + *index, "$(", 2) == 0)
	{
		return ;
	}
}

int ft_rule_five(char *line, t_token **head, int *index)
{
    if (ft_is_quoted(line, *index) == 0 && (line[*index] == '$' || line[*index] == '`'))
	{
		ft_substitution_control(line, head, index);
		if ((*head)->value == NULL)
			(*head)->type = WORD_T;
		(*head)->value = ft_append_char((*head)->value, line[*index]);
		*index += 1;
		return (1);
	}
	return (0);
}

int ft_rule_six(char *line, t_token **head, int *index)
{
    if(ft_strchr(">|<", line[*index]) && !ft_is_quoted(line, *index))
    {
        if((*head)->value != NULL)
            ft_token_delimiter(head);
        (*head)->value = ft_append_char((*head)->value, line[*index]);
        (*head)->type = OPERATOR_T;
        (*index)++;
        return (1);
    }
    return (0);
}

int ft_rule_seven(char *line, t_token **head, int *index)
{   
    if((ft_strchr(" ", line[*index])) && (!ft_is_quoted(line, *index)))
    {
        while ((ft_strchr(" \t\r\v\f", line[*index])) && (line[*index] != '\0'))
            (*index)++;
        if(((*head)->value != NULL) && (line[*index] != '\0'))
        {
            ft_token_delimiter(head);
        }
        return (1);
    }
    return (0);
}

int ft_rule_eight(char *line, t_token **head, int *index)
{
    if((*head)->type == WORD_T)
    {
        (*head)->value = ft_append_char((*head)->value, line[*index]);
        (*index)++;
        return (1);
    }
    return (0);
}

int ft_rule_nine(char *line, int *index)
{
    if(line[*index] == '#')
    {
        while(line[*index] != '\n' && line[*index] != '\0')
            (*index)++;
        return (1);
    }
    return (0);
}

int ft_rule_ten(char *line, t_token **head, int *index)
{
    if(line[*index] != '\0')
    {
        (*head)->value = ft_append_char((*head)->value, line[*index]);
        (*head)->type = WORD_T;
        (*index)++;
        return (1);
    }
    return (0);
}
