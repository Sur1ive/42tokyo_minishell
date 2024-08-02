/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:49:58 by yxu               #+#    #+#             */
/*   Updated: 2024/08/02 12:14:58 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <errno.h>
# include "../libft/libft.h"

# define PATH_MAX 4096

void	free2(char **p);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
int		ft_setenv(char ***envpp, char *name, char *value);
char	*ft_getenv(char **envp, char *name);
char	**ft_getenv_item(char **envp, char *name);
int		ft_count(char **p);
char	**parseline(char *line);
int		init_envp(char ***envpp);
int		exec(char **args, char ***envpp);
int		echo(char **args);
int		pwd(void);
int		env(char **envp);
int		cd(char **args, char ***envpp);
int		export(char **args, char ***envpp);
int		unset(char **args, char ***envpp);
void	set_signal(void);

#endif
