#include "../../inc/minitry.h"

t_command   retrieve_cmd(char *input)
{
    t_darray tab;
    t_lexer	lexer;
    int		i;
	int		j;

    i = 0;
	j = 0;
    init_array(&tab, 10);
	if (!tab.content)
		return ((void)NULL);
    while (input[i]) //identifier aussi les WORDS
    {
        if (ft_isspace(input[i]) = 0)
            i++;
        else if (input[i] == '|') //erreur si j'ai "||" ou que | est mon premier terme ? des aue j'ai un pipe -> ajouter une ligne a ma struc et le mettre en premier terme de la nouvelle ligne
			tab[j].type = PIPE //indiquer sa position qq part ? 
		else if (input[i] == '<<') //utils str_cmp  si "<>"/"><" erreur de syntaxe
		else if (input[i] == '<' && input[i] == input[i + 1])
			lexer->operator = REDIR_HEREDOC;
		else if (input[i] == '>>')
			lexer->operator = REDIR_APP;
		else if (input[i] == '<')
			lexer->operator = REDIR_IN;
		else if (input[i] == '>')
			lexer->operator = REDIR_OUT;
			tab[j] = new_token;
		else if (input[i] == '\"')
		{
			while (input[i] != '\"') //ici on doit conserver les variables d'env uniquement
			{
				if (input[i] == '\0')
					error_fct();
				stocker chaque carctere dans une string //puis transferer cette strinf dans tab et puis la free ou direct dans tab ?
				i++;
			}
		}
		else if (input[i] == '\'')
		{
			lexer->operator = QUOTE;
			i++;
			while (input[i] != '\'') //ici on gere rien du tout c'est un WORD, \n, \t, \v, \f, \r
			{
				if (input[i] == '\0')
					error_fct();
				stocker chaque carctere dans une string
				i++;
			}
		}
		i++;
    }
}

// maybe give return check?
char	init_array(t_darray* darray, size_t block_size)
{
	darray->block = block_size;
	darray->max_size = block_size;
	darray->actual_size = 0;
	darray->content = malloc(sizeof(t_lexer)*block_size);
	if (!darray->content)
		return (0);
	return (1);
}

int	append_array(t_darray darray)
{

}

void	free_temp_array(t_darray* darray)
{
	int	i;

	i = 0;
	while (i < darray->actual_size)
	{
		free(darray->content[i].word);
		i++;
	}
	free(darray->content);
}

t_darray	realloc_array(t_darray *darray)
{
	t_lexer	*new_content;

	darray->max_size = darray->max_size + darray->block;
	new_content = malloc(sizeof(t_lexer)*darray->max_size);
	// copier darray dans new_array
	free_temp_array(darray);
	darray->content = new_content;
	return (*darray);
}
