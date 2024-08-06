/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:49:58 by yxu               #+#    #+#             */
/*   Updated: 2024/08/06 21:19:55 by yxu              ###   ########.fr       */
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

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

// init functions
void	set_signal(void);
int		init_envp(char ***envpp);

// processor functions
char	**parseline(char *line);
int		exec(char **args, char ***envpp);
int		exec_cmd(char **args, char ***envpp);
int		exec_file(char **args, char ***envpp);

// functions about environment variables
int		ft_setenv(char ***envpp, char *name, char *value);
char	*ft_getenv(char **envp, char *name);
char	**ft_getenv_item(char **envp, char *name);

// builtin funcitons
int		echo(char **args);
int		pwd(void);
int		env(char **envp);
int		cd(char **args, char ***envpp);
int		export(char **args, char ***envpp);
int		unset(char **args, char ***envpp);

// utilities
void	free2(char **p);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
int		ft_count(char **p);

#endif
