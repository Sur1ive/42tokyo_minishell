/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:49:58 by yxu               #+#    #+#             */
/*   Updated: 2024/09/16 19:48:23 by nakagawashi      ###   ########.fr       */
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
# include <stdbool.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_flags
{
	char	*start;
	bool	in_word;
	bool	new_word_start;
}	t_flags;

typedef struct s_cmd_table
{
	struct s_cmd_table	*next;
	char				**cmd;
	int					in;
	int					out;
}	t_cmd_table;

/*------------------init functions---------------------*/

// ctrl-c, ctrl-d, ctrl-\の動作を設定する。
void	set_signal(void);

// 環境変数を初期化する。環境変数の配列envpはmallocで確保するため、
// プログラム終了時にfreeする必要がある。
int		init_envp(char ***envpp);

/*--------------processor functions --------------------*/

// Inputを解析する(未完成)
t_cmd_table	*parseline(char *line, char **envp);

// 解析されたcommand lineを実行する。
// args example: ["./minishell", "echo", "-n", "hello" "world"]
// コマンドに'/'が含まれる場合、exec_file()を呼び出す、それ以外の場合はexec_cmd()
int		exec(char **args, char ***envpp);

// filepathで指定されたファイルを実行する
int		exec_file(char *filepath, char **args, char **envp);

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

int		is_builtin(char *command);
int		exec_bulitin(char **args, char ***envpp);
int		echo(char **args);
int		pwd(void);
int		env(char **envp);
int		cd(char **args, char ***envpp);
int		export(char **args, char ***envpp);
void	builtin_exit(char **envp);

// unsetする環境変数をfreeしなく、空の文字列に書き換える
int		unset(char **args, char ***envpp);

/*---------------------utilities-------------------------*/

// ダブルフリー
void	free2(char **p);

// トリプルジョイン
char	*ft_strjoin3(char *s1, char *s2, char *s3);

// 要素数をカウントする
int		ft_count(char **p);

char	*ft_strndup(char *s, size_t n);

char	*ft_strncat(char *dst, const char *src, size_t n);

/*---------------------utilitie-------------------------*/

#endif
