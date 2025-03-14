/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:33:24 by iwaslet           #+#    #+#             */
/*   Updated: 2025/03/04 12:44:42 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "minishell_lib.h"
# include "minishell_enum.h"
# include "minishell_struct.h"
# include "minishell_function.h"

extern volatile sig_atomic_t	g_signal_received;

#endif
