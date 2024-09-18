#include "../../inc/minitry.h"

t_command   retrieve_cmd(char *input)
{
    t_darray tab;
    int		i;
	int		j;

    i = 0;
	j = 0;
    init_array(&tab, 10);
	if (!tab.content)
		return ((void)NULL);
    while (input[i]) //j'itere ou moi ptdr ???
    {
        if (ft_isspace(input[i]) = 0)
            i++;
        else if (input[i] == '|')
			tab.content[j] = create_pipe(input, i, tab.content[j]); //j++;
		else if (input[i] == '<')
			tab.content[j] = create_redirect_in(input, i, tab.content[j]);
		else if (input[i] == '>')
			tab.content[j] = create_redirect_out(input, i, tab.content[j]);
		else if (input[i] == '\"')
		{
			tab.content[j] = create_doubleq(input, i, tab.content[j]);
			if (!tab.content[j].word)
				error_fct();
		}
		else if (input[i] == '\'')
		{
			tab.content[j] = create_simpleq(input, i, tab.content[j]);
			if (!tab.content[j].word)
				error_fct();
		}
		else
			tab.content[j] = create_word(input, i, tab.content[j]);
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
	int		i;

	i = 0;
	darray->max_size = darray->max_size + darray->block;
	new_content = malloc(sizeof(t_lexer)*darray->max_size);
	while (&darray->content[i])
	{
		new_content[i] = darray->content[i];
		i++;
	}
	free_temp_array(darray);
	darray->content = new_content;
	return (*darray);
}
