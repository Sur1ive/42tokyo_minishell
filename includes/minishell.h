/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:49:58 by yxu               #+#    #+#             */
/*   Updated: 2024/10/02 22:46:12 by yxu              ###   ########.fr       */
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

// exit code管理
int			set_exit_code(int new_exit_code, int mode);
# define EC_RDONLY 1

// exit_codeの値
# define EXIT_SUCCESS 0
# define GENERAL_ERR 1
# define MISUSE_OF_BUILTINS 2
# define CANNOT_EXEC 126
# define CMD_NOT_FOUND 127
# define INVALID_EXITCODE 128
# define MANUAL_TERM 130
# define MANUAL_QUIT 131
# define EXITCODE_OUT_OF_RANGE 255

typedef struct s_flags
{
	char	*start;
	char	quote_char;
	bool	in_word;
	bool	in_quote;
}	t_flags;

typedef struct s_redirection
{
	char					*op;
	char					*fd_name;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_cmd_table
{
	struct s_cmd_table	*prev;
	struct s_cmd_table	*next;
	t_redirection		*redir;
	char				**cmd;
	int					in;
	int					out;
	int					pid;
}	t_cmd_table;

/*------------------init functions---------------------*/

// ctrl-c, ctrl-\の動作を設定する。
void		set_signal(int mode);
void		mod_sigquit_key(int mode);
# define S_ENABLE 0
# define S_RESTORE 0
# define S_DISABLE 1

// 環境変数を初期化する。環境変数の配列envpはmallocで確保するため、
// プログラム終了時にfreeする必要がある。
int			init_envp(char ***envpp);

/*--------------processor functions --------------------*/

// Inputを解析する(未完成)
t_cmd_table	*parseline(char *line, char **envp);

// 一つのcommand lineを実行する。
// PATHを使った外部ファイル検索や、builtin関数を呼び出すことができる。
int			exec(char **args, char ***envpp, t_cmd_table *cmd, pid_t pid);

// cmd tableのリストにあるすべてのコマンドを実行する
void		executor(t_cmd_table *cmd, char ***envpp);
void		freecmd(t_cmd_table *cmd);

void		shell_exit(int status);

/*----------functions about environment variables--------*/

/*	env: "A=B"形式(例外:空の文字列)の文字列。 例: "PWD=/home"
	envp: 環境変数の配列。例: ["PWD=/home", "", "PATH=/bin"]
	envpp: envpを指すポインタ。
	envとenvpはmallocで確保する。      　　　　　　　　　　　*/

// 環境変数名=nameの環境変数の値をvalueに設定する
// 例: ft_setenv(envpp, "HOME", "/home/yxu")
int			ft_setenv(char ***envpp, char *name, char *value);

// 環境変数名=nameの環境変数の値を返す
// 例: ft_getenv(envp, "HOME")
char		*ft_getenv(char **envp, char *name);

// 環境変数名=nameの環境変数のポインタを返す
// 例: ft_getenv_item(envp, "HOME")
char		**ft_getenv_item(char **envp, char *name);

/*-----------------builtin funcitons---------------------*/

int			is_builtin(char *command);
int			exec_builtin(char **args, char ***envpp, pid_t pid);
int			echo(char **args);
int			pwd(void);
int			env(char **envp);
int			cd(char **args, char ***envpp);
int			export(char **args, char ***envpp);
int			builtin_exit(char **args, pid_t pid);

// unsetする環境変数をfreeしなく、空の文字列に書き換える
int			unset(char **args, char ***envpp);

/*---------------------utilities-------------------------*/

// ダブルフリー
void		free2(char **p);

// トリプルジョイン
char		*ft_strjoin3(char *s1, char *s2, char *s3);

// 要素数をカウントする
int			ft_count(char **p);

char		*ft_strndup(char *s, size_t n);
char		**ft_strdup2(char **arr);
char		*ft_strncat(char *dst, const char *src, size_t n);
int			replace_io(int in, int out);

#endif
