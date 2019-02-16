/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 22:16:00 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/15 18:37:34 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"

char	*get_value(char *env_var)
{
	int i;

	i = 0;
	while (valid_env_char(env_var[i]))
		i++;
	if (env_var[i] == 0)
		return (env_var + i);
	return (env_var + i + 1);
}
