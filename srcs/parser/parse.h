/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:42:36 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/26 08:13:50 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

int	syntax_error(char *cmd, char *next_cmd);
int	create_next_cmd(t_parsed_cmd **current, char **cmds, int *i, int *index);
t_parsed_cmd	*parser(char **cmds, char **envp);
t_parsed_cmd *handle_env(t_parsed_cmd *cmd, char **envp);
char	*ft_strjoin_free(char const *s1, char const *s2);
int	count_words(char *line);
t_parsed_cmd	*create_p_cmd(void);
t_cmd_table	*create_cmd_table_entry(t_parsed_cmd *p_cmds);
void	free_p_table(t_parsed_cmd *table, int type);
void	free_cmd_table(t_cmd_table *table);
int	is_redirection(char *token);
void	*ft_realloc(void *ptr, size_t new_size);
ssize_t	ft_getline(char **lineptr, size_t *n);
int	count_arg(char **command);
char	**lexer(char *line, char **command);
t_cmd_table	*exec_preparator(t_parsed_cmd *cmds);
char	*handle_token(char *cmd, char **envp, bool	flag);

#endif