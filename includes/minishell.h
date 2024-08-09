/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:49:58 by yxu               #+#    #+#             */
/*   Updated: 2024/08/09 16:09:03 by yxu              ###   ########.fr       */
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

/*------------------init functions---------------------*/

// ctrl-c, ctrl-d, ctrl-\の動作を設定する。
void	set_signal(void);

// 環境変数を初期化する。環境変数の配列envpはmallocで確保するため、
// プログラム終了時にfreeする必要がある。
int		init_envp(char ***envpp);

/*--------------processor functions --------------------*/

// Inputを解析する(未完成)
char	**parseline(char *line);

// 解析されたcommand lineを実行する。
// args example: ["./minishell", "echo", "-n", "hello" "world"]
// コマンドに'/'が含まれる場合、exec_file()を呼び出す、それ以外の場合はexec_cmd()
// echo hello world ----> exec_cmd()
// ./minishell  ----> exec_file()
int		exec(char **args, char ***envpp);

// 環境変数PATH配下にで指定されたコマンドを探して実行する。
int		exec_cmd(char **args, char ***envpp);

// args[0]で指定されたファイルを実行する
int		exec_file(char **args, char ***envpp);

/*----------functions about environment variables--------*/

/*	env: "A=B"形式(例外:空の文字列)の文字列。 例: "PWD=/home"
	envp: 環境変数の配列。例: ["PWD=/home", "", "PATH=/bin"]
	envpp: envpを指すポインタ。
	envとenvpはmallocで確保する。      　　　　　　　　　　　*/

// 環境変数名=nameの環境変数の値をvalueに設定する
// 例: ft_setenv(envpp, "HOME", "/home/yxu")
int		ft_setenv(char ***envpp, char *name, char *value);

// 環境変数名=nameの環境変数の値を返す
// 例: ft_getenv(envp, "HOME")
char	*ft_getenv(char **envp, char *name);

// 環境変数名=nameの環境変数のポインタを返す
// 例: ft_getenv_item(envp, "HOME")
char	**ft_getenv_item(char **envp, char *name);

/*-----------------builtin funcitons---------------------*/

int		echo(char **args);
int		pwd(void);
int		env(char **envp);
int		cd(char **args, char ***envpp);
int		export(char **args, char ***envpp);

// unsetする環境変数をfreeしなく、空の文字列に書き換える
int		unset(char **args, char ***envpp);

/*---------------------utilities-------------------------*/

// ダブルフリー
void	free2(char **p);

// トリプルジョイン
char	*ft_strjoin3(char *s1, char *s2, char *s3);

// 要素数をカウントする
int		ft_count(char **p);

#endif
