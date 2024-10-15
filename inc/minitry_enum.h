/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry_enum.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:02:51 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/15 14:15:42 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINITRY_ENUM_H

# define MINITRY_ENUM_H

/**
 * An enum to identify the different type of redirection that can affect a command
 *
 * REDIR_IN :	<
 * REDIR_OUT:	>	
 * REDIR_HEREDOC : <<
 * REDIR_APPEND :	>>
 */
enum e_tokens {
    PIPE = 1,
    QUOTE,
    D_QUOTE,
    WORD,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APP,
    REDIR_HEREDOC
};

enum e_builtin {
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum e_error {
	OK,
	OPEN_FILE
};

# define READ_FROM 0
# define WRITE_TO 1

#endif