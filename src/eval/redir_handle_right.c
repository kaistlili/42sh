/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:46:08 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/21 16:54:41 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eval.h"

static int	get_open_flags(t_token_type op)
{
	if (op == GREAT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (op == DGREAT)
		return (O_WRONLY | O_APPEND | O_CREAT);
	return (O_RDONLY);
}

static int ambiguous_redir(char *file)
{
	ft_dprintf(STDERR_FILENO, "21sh: %s : ambiguous redirection\n"
		, file);
	return (-1);
}

static int fd_aggregator(int *left_fd, int *right_fd, t_redir *redir)
{
	t_redir tmp;

	ft_bzero(&tmp, sizeof(t_redir));
	if (!ft_isalldigit(redir->right->data.str))
	{	
		if ((redir->op->type == LESSAND)
			|| ((redir->op->type == GREATAND) && (redir->left)))
					return (ambiguous_redir(redir->right->data.str));
		else /* case >& word, equivalent to > word 2>&1*/ 
		{ /*we construct tmp redir for '> word' apply it, then proceed with '2>&1' */
			tmp.op = redir->op;
			tmp.op->type = GREAT;
			tmp.right = redir->right;
			if (apply_redir(&tmp))
				return (-1);
			redir->op->type = GREATAND;
			*left_fd = 2;
			*right_fd = 1;
			return (0);
		}
	}
	*right_fd = ft_atoi(redir->right->data.str);
	return (0);
}
/*
 * command left_fd [>,<,>&,<&,>>,<<] right_fd
 */
int	handle_right(int *left_fd, int *right_fd, t_redir *redir)
{
	int oflag;

	if ((redir->op->type == GREATAND) || (redir->op->type == LESSAND))
	{
		if (ft_strequ(redir->right->data.str, "-"))
		{
			close(*left_fd);
			return (1);
		}
		return (fd_aggregator(left_fd, right_fd, redir));
		//check for ambiguous redir here (data.str has to be all digit)
	}
	oflag = get_open_flags(redir->op->type);
	*right_fd = open(redir->right->data.str, oflag, 0644); 
	if (*right_fd == -1)
	{
		exec_error(BIN_NOT_FOUND, redir->right->data.str);
		return (-1);
	}
	return (0);
}