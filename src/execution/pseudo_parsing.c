/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:57:01 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/02 12:13:23 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

static int	count_nb_of_cmd(char *input)
{
	int	i = 0;

	while (*input)
	{
		if (*input == '|')
			i++;
		input++;
	}
	return (i + 1);
}

static void	set_all_members_to_NULL(t_command *tab, int size)
{
	int	i = 0;

	while (i != size)
	{
		tab[i].cmd = NULL;
		tab[i].redirection.array = NULL;
		tab[i].redirection.size = 0;
		tab[i].error.str_perror = NULL; 
		tab[i].error.code = OK;
		i++;
	}
}

int	 count_redir(char **cmd)
{
	int i = 0;
	int	nb = 0;

	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '<'))
			nb++;
		else if (ft_strchr(cmd[i], '>'))
			nb++;
		i++;
	}
	return (nb);
}

enum e_tokens	which_redir(char *arg)
{
	enum e_tokens	type;

	type = -1;

	if (!ft_strncmp(arg, "<", 1))
		type = REDIR_IN;
	if (arg[1] == '<')
		type = REDIR_HEREDOC;
	else if (!ft_strncmp(arg, ">", 1))
		type  = REDIR_OUT;
	if (arg[1] == '>')
		type = REDIR_APP;
	return (type);
}

t_redirect	new_redir(char *arg)
{
	t_redirect	redir;
	int	char_len;

	redir.type = which_redir(arg);
	//ft_printf("REDIR_TYPE : %d\n", redir.type);
	char_len = 2;
	if (redir.type == REDIR_IN || redir.type == REDIR_OUT)
		char_len = 1;
	redir.filename = ft_strdup(arg + char_len);
	redir.hd_delimiter = NULL;
	return (redir);
}

t_redir_array	fill_redir_array(t_command cmd)
{
	int	i = 0;
	t_redir_array redir;
	int	n = 0;

	redir.size = count_redir(cmd.cmd);
	redir.array = malloc(sizeof(t_redirect) * redir.size);
	while (cmd.cmd[i])
	{
		if (!ft_strncmp(cmd.cmd[i], "<", 1) || !ft_strncmp(cmd.cmd[i], ">", 1))
		{
			redir.array[n] = new_redir(cmd.cmd[i]);
			n++;
		}
		i++;
	}
	return (redir);
}

char **construct_cmd(char **dirty_cmd, int redir_size)
{
	int	i = 0;
	int	j = 0;
	char **clean_cmd;

	clean_cmd = NULL;
	while (dirty_cmd[i])
		i++;
	i = i - redir_size;
	clean_cmd = malloc(sizeof(char *) * (i + 1));
	if (!clean_cmd)
		return (NULL);
	i = 0 ;
	while (dirty_cmd[i])
	{
		if (!ft_strchr(dirty_cmd[i], '<') && !ft_strchr(dirty_cmd[i], '>'))
		{
			clean_cmd[j] = ft_strdup(dirty_cmd[i]);
			j++;
		}
		i++;
	}
	free_tab_char(dirty_cmd);
	clean_cmd[j] = NULL;
	return(clean_cmd);
}

static void parse_cmd(t_shell *shell, t_command *tab, char *input)
{
	int i;
	char **input_split;

	i = 0;
	input_split = ft_split(input, '|');
	while(input_split[i])
	{
		tab[i].cmd = ft_split(input_split[i], ' ');
		i++;
	}
	free_tab_char(input_split);
	shell->tab = tab;
	i = 0;
	while (i != shell->tab_size)
	{
		shell->tab[i].redirection = fill_redir_array(shell->tab[i]);
		i++;
	}
	i = 0;
	while (i != shell->tab_size)
	{
		shell->tab[i].cmd = construct_cmd(shell->tab[i].cmd, shell->tab[i].redirection.size);
		shell->tab[i].fd_in = STDIN_FILENO;
		shell->tab[i].fd_out = STDOUT_FILENO;
		i++;
	}
}

t_command *pseudo_parsing(t_shell *shell, char *input)
{
	t_command *tab;

	shell->tab_size = count_nb_of_cmd(input);
	tab	= malloc(sizeof(*tab) * (shell->tab_size));
	if (!tab)
		exit_error(shell, "malloc");
	set_all_members_to_NULL(tab, shell->tab_size);
	parse_cmd(shell, tab, input);
//	ft_print_cmd(shell);
	return (tab);
}

void	print_redir_type(int token)
{
	if (token == REDIR_IN)
		ft_printf("REDIR_IN");
	else if (token == REDIR_OUT)
		ft_printf("REDIR_OUT");
	else if (token == REDIR_APP)
		ft_printf("REDIR_APP");
	else if (token == REDIR_HEREDOC)
		ft_printf("REDIR_HEREDOC");
	else 
		ft_printf("IS NOT A REDIR");
}

void	print_redirection(t_redir_array redir)
{
	int	i = 0;
	ft_printf("redir.size : %d\n", redir.size);
	while (i != redir.size)
	{
		ft_printf("redir.filename : %s, ", redir.array[i].filename);
		print_redir_type(redir.array[i].type);
		ft_printf("\n");
		i++;
	}
}

void	ft_print_cmd(t_shell *shell)
{
	int	i = 0;
	int	j = 0;

	ft_printf("tab size : %d\n", shell->tab_size);
	if (!shell->tab || !shell->tab->cmd)
		return;
	while (i != shell->tab_size)
	{
		ft_printf("-------------------------------\n");
		while (shell->tab[i].cmd[j] != NULL)
		{
			ft_printf("cmd[%d] : %s\n", j, shell->tab[i].cmd[j]);
			j++;
		}
		print_redirection(shell->tab[i].redirection);
		j = 0;
		i++;
	}
	ft_printf("-------------------------------\n");
}
