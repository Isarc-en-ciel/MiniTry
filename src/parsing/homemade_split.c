/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   homemade_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:48:46 by iwaslet           #+#    #+#             */
/*   Updated: 2024/09/19 18:06:21 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int pars_it(char *input)
{
    if (check_syntax(input) != 0)
        return (error_fct());
    ft_strtrim(input, ' ');
    return (0);
}

char    **My_Split(char *input)
{
    //trouver tous les whitespace puis les separateurs
    //tout separer en "blocs" (tab)
    //parcourir la liste/tab et reseparer aux pipes
}
/* FONCTIONS NECESSSAIRES
- str_cmp
- allouer memoire struct
- strtrim pour enlever les espaces inutiles autour
- split
- strlen
- strtrim ?
- isspace (personalise mdr)
- pleins de free et de mallocs sa mere
*/

char	**create_tab(int nbr)
{
	int 	size;
    char    **tab;

	size = nbr + 1;
    tab = malloc(sizeof(char) * size); //type sera pas forcement char
    return (tab);
}

int is_separator(char *str)
{
	//liste des separateurs: < 60, > 62, | 124,  32, >> append, << here-doc et les separateurs ou faut gerer les espaces: " 34, ' 39
}

void    save_space(char *str, char c)
{
    while (str)
    {
        if (str = c)
        {
            str++;
            while (str != c)
            {
                if (str = 32)
                    str = -32;
                str++;
            }
        }
        str++;
    }
}


/*
DYNAMIC ARRAY IDEA
struct s_darray
{
    t_lexer*   content;
    size_t  max_size;       size of malloced memory   //maximum number of elements (determined by block_size)
    size_t  type_size;      size of element type = sizeof(t_lexer)
    size_t  actual_size;    amount of bytes in use  // index for the last element in use -1  (actual elements used)
    size_t  block_size;     size of blocks  //1 bloc is several elements so that I dont have to reallocate too often
}   t_darray;

init_array(amount, type_size);
append(void* element);              if ((size + 1) * type_size > max_size) --> realloc with an extra block
                                        else just add element and size++ and stuff
realloc_array();                    new void* content, memcopy(void* content, void* new, actual_size), free old one
at(index);                          if (index <= size) { index * type_size }
delete(delete*(void*))              if (delete != NULL) { use delete ft on all elements }
                                        (most of the time it's either delete(NULL) or delete(free()))

void* content = [][][][][]       = 5 mem blocks of size type_size (e.g. int or token)
*/


// si un malloc foire ou que ce soit, on peut exit le programme

/*plutot qu'un double tableau, simple tableau, 
compter mes pipes pour eliminer les erreur de sytaxe 
et creer un tableau de commandes de la bonne taille direct 
et sortir de ma boucle a chaque pipe*/

//utils str_cmp  si "<>"/"><" erreur de syntaxe

/*while()
{
    array[i]
    while(array[i] = PIPE)
    {
        array[i][j]
    }
}*/

/*
darray implentations:
    - init_array(block_size, type_size);
    - append(element);      // calls realloc if needed (actual_size >= max_size)
    - realloc();            // expand :) (and memcopy) (and also free content)
    - delete();             // free content
*/

/*example_function() 
{
    t_lexer new;
    append(new); // memcopy new
}*/
