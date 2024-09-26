/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:20:28 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/26 15:50:20 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITRY_H

#define MINITRY_H

#include "minitry_lib.h"
#include "minitry_struct.h"
#include "minitry_function.h"

# define READ_FROM 0
# define WRITE_TO 1

enum e_builtin {
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};


#endif
