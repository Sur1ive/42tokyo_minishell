/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 03:42:36 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/10/01 02:11:49 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

int			syntax_error(char **cmd);
void		*ft_realloc(void *ptr, size_t new_size);
ssize_t		ft_getline(char **lineptr, size_t *n);
int			count_arg(char **command);
int			count_words(char *line);
char		*handle_token(char *cmd, char **envp, bool	flag, bool *env_flag);
int			handle_pipe(t_cmd_table **current);
char	*ft_strjoin_free(char const *s1, char const *s2);

int			is_redirection(char *token);
t_cmd_table	*create_cmd_table_entry(void);

char		**lexer(char *line, char **command);
t_cmd_table	*parser(char **cmds);
t_cmd_table	*expand_envs(t_cmd_table	*table, char **envp);
t_cmd_table	*exec_preparator(t_cmd_table *cmds, char **envp);

void		free_redirections(t_redirection *redir);
void		free_table(t_cmd_table *table);

#endif