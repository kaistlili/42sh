/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:13:04 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/21 18:00:24 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_core.h"
#include "readline.h"

t_list *g_hst[4] = {NULL, NULL, NULL, NULL};

void	hstadd(char *str)
{
	if (g_hst[0] && !ft_strcmp(g_hst[0]->content, str))
		return ;
	ft_lstadd(&g_hst[0], ft_lstnew(str, 0));
}

int		hstread(char **env)
{
	int		fd;
	char	*line;
	char	*path;
	char	*home;

	if (!(home = envchrr(env, "HOME"))
		|| !(path = ft_zprintf("%s/%s", home, ".21sh_history")))
		return (0);
	fd = open(path, O_RDONLY);
	ft_strdel(&path);
	if (fd < 0)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		ft_lstadd(&g_hst[0], ft_lstnew(line, 1));
		ft_strdel(&line);
	}
	close(fd);
	return (1);
}

char	*hstchc(char *s)
{
	t_list *lst;

	lst = g_hst[0];
	if (!s[0] || !s)
		return (NULL);
	while (lst)
	{
		if (ft_strstr(lst->content, s))
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

char	*hstnext(char *s)
{
	if (!g_hst[1])
	{
		hstreset();
		g_hst[2] = ft_lstnew(s, 0);
		if (!g_hst[0])
			return (NULL);
		g_hst[1] = g_hst[0];
		return (g_hst[0]->content);
	}
	if (g_hst[1]->next)
	{
		g_hst[1] = g_hst[1]->next;
		return (g_hst[1]->content);
	}
	return (NULL);
}

char	*hstprev(void)
{
	if (g_hst[1] && g_hst[1]->prev)
	{
		g_hst[1] = g_hst[1]->prev;
		return (g_hst[1]->content);
	}
	else if (g_hst[2])
	{
		g_hst[1] = NULL;
		return (g_hst[2]->content);
	}
	return (NULL);
}

void	hstreset(void)
{
	g_hst[1] = NULL;
	if (g_hst[2])
	{
		ft_strdel((char**)&g_hst[2]->content);
		free(g_hst[2]);
	}
	g_hst[2] = NULL;
}

void	hstwrite(int fd, t_list *lst)
{
	if (!lst || lst->content_size)
		return ;
	hstwrite(fd, lst->next);
	ft_dprintf(fd, "%s\n", lst->content);
}

void	hstaddfile(char	**env)
{
	int		fd;
	char	*path;
	char	*home;

	path = NULL;
	if (!(home = envchrr(env, "HOME"))
		|| !(path = ft_zprintf("%s/%s", home, ".21sh_history")))
		return ;
	fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0600);
	ft_strdel(&path);
	if (fd < 0)
		return ;
	hstwrite(fd, g_hst[0]);
	close(fd);
}
