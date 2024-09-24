#include "../../inc/minitry.h"

int print_token_tab(t_darray *cmd)
{
    size_t i;

    i = 0;
    while(i < cmd->actual_size)
    {
        ft_printf("Token has %d space, and has word %s \n",
         cmd->content[i].is_there_a_space, cmd->content[i].word);
        i++;
    }
    return (0);
}
