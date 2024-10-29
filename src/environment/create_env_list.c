/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:36:39 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/29 17:28:02 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

t_env_list	*new_env_list(char *key, char *value)
{
	t_env_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = value;
	new->key = key;
	new->next = NULL;
	return (new);
}

void	lst_addback(t_env_list **head, t_env_list *new)
{
	t_env_list	*tmp;

	if (!head || !new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

static void	*free_struct(t_env_list **head, char **str_tab)
{
	if (head && *head)
		destroy_lst(head);
	if (str_tab)
		free_tab_char(str_tab);
	return (NULL);
}

t_env_list	*array_to_list(char **env)
{
	t_env_list	*head;
	t_env_list	*new;
	char		**dico;
	int			i;

	head = NULL;
	i = 0;
	while (env[i])
	{
		dico = ft_split(env[i], '=');
		if (!dico)
			return ((t_env_list*)free_struct(&head, dico));
		new = new_env_list(dico[0], dico[1]);
		if (!new)
			return ((t_env_list*)free_struct(&head, dico));
		new = new_env_list(dico[0], dico[1]);
		lst_addback(&head, new);
		//free_tab_char(dico);
		i++;
	}
	return (head);
}

char **list_to_array(t_env_list **head)
{
	char		**env;
	t_env_list	*tmp;
	int			i;

	tmp = *head;
	env = NULL;
	i = 0;
	env = malloc(sizeof(*env) * (get_list_size(*head) + 1));
	if (!env)
		return ((char**)free_struct(head, env));
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->key, "=", NO_MALLOC);
		if (!env[i])
			return ((char**)free_struct(head, env));
		env[i] = ft_strjoin(env[i], tmp->value,NO_MALLOC);
		if (!env[i])
			return ((char**)free_struct(head, env));
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	destroy_lst(head);
	return (env);
}

void	ft_print_list(t_env_list *head)
{
	t_env_list	*tmp;

	tmp = head;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
