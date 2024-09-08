/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakagawashinta <nakagawashinta@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:58:59 by nakagawashi       #+#    #+#             */
/*   Updated: 2024/09/08 18:01:30 by nakagawashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_table *create_cmd_table_entry(void)
{
	t_cmd_table	*entry;

	entry = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!entry)
		return (NULL);
	entry->cmd = NULL;
	entry->in = 0;
	entry->out = 1;
	entry->next = NULL;
	return (entry);
}

void	free_cmd_table(t_cmd_table *table)
{
	t_cmd_table	*tmp;

	while (table)
	{
		tmp = table;
		table = table->next;
		free(tmp);
	}
}

int	is_redirection(char *token)
{
	return (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0 ||
			strcmp(token, "<") == 0 || strcmp(token, "<<") == 0);
}

int	handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;
	size_t	len;

	len = 0;
	line = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	printf("heredoc> ");
	while (getline(&line, &len, stdin) != -1)
	{
		// デリミタが見つかるまで標準入力を読み続ける
		printf("delimiter:%s\n",delimiter);
		printf("line:%s\n",line);
		if (strcmp(line, delimiter) == 0)
			break;
		// パイプの書き込み側に書き込む
		write(pipefd[1], line, strlen(line));
		printf("heredoc> ");
	}
	free(line);
	close(pipefd[1]); // 書き込み側を閉じる
	return (pipefd[0]); // 読み取り側のファイルディスクリプタを返す
}

int	count_arguments(char **command)
{
	int	count;
	int i;

	count = 0;
	i = 0;
	while (command[i] && !is_redirection(command[i]) && ft_strcmp(command[i], "|") != 0)
	{
		count++;
		i++;
	}
	return (count);
}

t_cmd_table *parse_command_with_redirection(char **command)
{
	t_cmd_table	*table;
	t_cmd_table	*current;
	int 		i;
	int			cmd_index;
	int			arg_count;

	cmd_index = 0;
	i = 0;
	table = create_cmd_table_entry();
	current = table;
	while (command[i])
	{
		if (current->cmd == NULL)
		{
			arg_count = count_arguments(&command[i]);
			current->cmd = malloc(sizeof(char *) * (arg_count + 1));
		}
		if (is_redirection(command[i]))
		{
			current->cmd[cmd_index] = NULL;
			if (strcmp(command[i], ">") == 0)
				current->out = open(command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (strcmp(command[i], ">>") == 0)
				current->out = open(command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (strcmp(command[i], "<") == 0)
				current->in = open(command[i + 1], O_RDONLY);
			else if (strcmp(command[i], "<<") == 0)
				current->in = handle_heredoc(command[i + 1]);
			i += 2;
		}
		else if (ft_strcmp(command[i], "|") == 0)
		{
			current->cmd[cmd_index] = NULL;
			cmd_index = 0;
			current->next = create_cmd_table_entry();
			current = current->next;
			i++;
		}
		else
		{
			current->cmd[cmd_index] = ft_strdup(command[i]);
			cmd_index++;
			i++;
		}
	}
	current -> cmd[cmd_index] = NULL;
	return (table);
}

// int main()
// {
//     char *command[] = {"cat", "<<", "EOF\n", NULL};

//     t_cmd_table *start;
//     int i;

//     start = parse_command_with_redirection(command);
//     while (start)
//     {
//         i = 0;
//         printf("Command: ");
//         while (start->cmd[i])
//         {
//             printf("%s ", start->cmd[i]);
//             i++;
//         }
//         printf("\n");
// 		printf("Input redirected from file descriptor: %d\n", start->in);
// 		printf("Output redirected to file descriptor: %d\n", start->out);
//         start = start->next;
//         printf("\n");
//     }
//     return 0;
// }