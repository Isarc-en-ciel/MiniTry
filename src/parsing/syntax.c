int check_open_quotes(char *str, char c, int j)
{
    int i;

    i = j;
    while (str++ != '\0')
     {
        if (str[i] = c)
            return (i - j);
        i++;
     }
    return (0);
}

int error_fct(t_darray tab)
{
    write (1, "SYNTAX ERROR\n", 13);
    if (tab)
        free_temp_array(tab);
    return (1);
}

int check_syntax(char *input)
{
    int i;
    
    i = 0;
    while (input[i])
    {
        if (input == '\"')
            i += check_open_quotes(input, '\"', i);
        else if (input == '\'')
            i += check_open_quotes(input, '\'', i);
        i++;
    }
    //passer une seule fois sur la string -> mettre un if a la fin si on a pas ferme une quote d'ici la fin c'est qu'on a une quote ouverte -> free et syntax error
    // donc en gros tokenifier d'office differament des qu'on trouve une quote puis changer tout en fonction de si elle est pas fermee
    // pas de double pipe, pas de &, pas plus de 2 > ou <, | comme dernier char, | vide
    return (0);
}

int pars_it(char *input)
{
    int i;

    i = 0;
    if (check_syntax(input) = 1)
        return (error_fct());
    while (input[i])
    {
        //avancer c par c, des qu'on a une quote -> check is_in_quote permanent
        // si in quote -> texte, si not -> regular parsing
        //a la fin -> if quote pas fermee -> free tout et syntax error
        // si y a un chiffre colle a un < ou >, c'est un fd ???
        // ">/< filename" toujours
    }
}

int ft_isspace(char c)
{
    if ((c > 8 && c < 14) || c == 32)
        return (0);
    return (1);
}
