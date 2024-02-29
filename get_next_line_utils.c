/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:00:35 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/29 14:29:37 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* la fonction ci dessous cherche un \n dans la liste donnée */

int	found_newline(t_list *stash)
{
	int	i;
	t_list	*current;

/* si stash est null il y aura rien à chercher donc on retourn 0 (donc un booléen) pour dire que ça s'est pas bien passé*/
	if (stash == NULL)
		return (0);
	current = ft_lst_last(stash);
	i = 0;
/* on va chercher dans la chaine de caratère stocké dans la liste si on trouve un \n */
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/* retourne un pointeur vers la dernière stash de la liste chainée */

t_list *ft_lst_last(t_list *stash)
{
	while (stash->next)
	{
		stash = stash->next;
	}
	return (stash);
}
