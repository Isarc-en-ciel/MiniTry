#include "../../inc/minitry.h"

int read_the_input(char **envp)
{
    char *input;
    t_darray    *cmd;

    (void)envp;

    cmd = NULL;
    while (1)
    {
        input = readline("gib comand pliz> ");
		if (!input)
		{
			ft_printf("Error input is NULL bouuuuh\n");
			break;
		}
		else if (ft_strlen(input) == 0)
			continue;
	    cmd = retrieve_cmd(input);
        if (cmd == NULL || cmd->content == NULL)
            return (1);
		add_history(input);
       	free(input);
	}
    return (0);
}

int main(int ac, char **av, char **envp)
{
    (void)av;

    if (ac != 1)
        return (1);
    read_the_input(envp);
    return (0);
}
