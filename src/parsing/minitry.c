#include "../../inc/minitry.h"

static	t_shell	*init_shell(void)
{
	t_shell *shell;

	shell = malloc(sizeof(*shell));
	if (!shell)
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	shell->tab = NULL;
	shell->env = NULL;
	shell->tab_size = 0;
	return (shell);
}

int read_the_input(char **envp)
{
    char *input;
    t_shell  *shell;

	shell = init_shell();
	shell->env = init_env(envp);
    while (1)
    {
        input = readline("gib comand pliz> ");
		if (!input)
			break;
		else if (ft_strlen(input) == 0)
			continue;
	//	shell.tab = retrieve_cmd(input); doesnt compile for the moment 
	//	if shell == null -> continue
		add_history(input);
		test_env(shell, input); // simple tests that wont disturb your workflow :)
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
