/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:17:35 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/12 18:37:33 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//garder cmb d'elem j'ai par cmd et cmb de cmd j'ai mdr

t_stock	*tab_cleaner(t_stock *tab)
{
	int		i;
	t_stock	*new_tab;

	i = 0;
	new_tab = malloc(sizeof(t_stock) * tab[0].nbr_cmd);
	if (!new_tab)
		return (NULL);
	print_stock_tab(tab, tab[0].nbr_cmd);
	while (i < tab[0].nbr_cmd)
	{
		new_tab[i] = (t_stock){0}; //mise a null > utile?
		new_tab[i].nbr_elem = 0;
		if (clean_cmd(tab[i].cmd, &new_tab[i].cmd, tab[i].nbr_elem, &new_tab[i].nbr_elem) == -1) //plutot envoyer tab ?
			return (NULL);
        new_tab[i].nbr_cmd = tab[0].nbr_cmd;
		i++;
	}
	printf("wola1 %d\n", i);
	print_stock_tab(new_tab, tab[0].nbr_cmd);
	printf("wola2\n");
	free_second_degree_tab(tab, tab[0].nbr_cmd);
	return (new_tab);
}

int	clean_cmd(t_lexer *cmd, t_lexer **new_cmd, int nbr_elem, int *new_nbr_elem)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*new_nbr_elem = count_new_elem(cmd, nbr_elem, new_nbr_elem);
	if (*new_nbr_elem == 0)
		return (-1);
	printf("wola y a %d elements\n", *new_nbr_elem);
	*new_cmd = malloc(sizeof(t_lexer) * (*new_nbr_elem));
	if (!*new_cmd)
		return (-1);
	while (i < nbr_elem)
	{
		if (cmd[i].is_there_a_space != -1)
		{
			printf("here's a number: %i\n", i);
			//*new_cmd[j] = (t_lexer){0}; //mise a null > utile?
			if (copy_token(cmd[i], &(new_cmd[0][j])) == -1) // il reecrit par dessus !
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	count_new_elem(t_lexer *cmd, int nbr_elem, int *new_nbr_elem)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < nbr_elem)
	{
		if (cmd[i].is_there_a_space != -1)
			n++;
		i++;
	}
	*new_nbr_elem = n;
	return (n);
}

int	copy_token(t_lexer cmd, t_lexer *new_cmd)
{
	// int	i;

	printf("HERE\n");
	(new_cmd)->is_there_a_space = cmd.is_there_a_space;
	(new_cmd)->type = cmd.type;
	(new_cmd)->word = NULL;
	if (cmd.word)
	{
		// i = ft_strlen(cmd.word);
		(new_cmd)->word = ft_strdup(cmd.word); /*malloc(sizeof(char) * i);*/
		if (!(new_cmd)->word)
			return (-1);
		/*(new_cmd)->word = ft_strcpy(cmd.word, (new_cmd)->word);*/
	}
	return (0);
}
