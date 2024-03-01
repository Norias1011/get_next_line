/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:27:06 by akinzeli          #+#    #+#             */
/*   Updated: 2024/02/29 16:39:33 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash; // reserve de caractère lu avec la fonction read
	char		*line; // 
	int		*count_read; //nombre de caractère lu par read

	stash = NULL;
	/* si le fichier est vide, ou que le buffer size est de 0 ou négatif ou que le fichier ne peut pas être lu (on aura un chiffre négatif) */
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
		return (NULL);
	count_read = 1;
	line = NULL;
	/* read from fd and add to the linked list. On envois un pointeur pour récupérer le résultat*/
	read_and_stash(fd, &stash, &count_read);
	/* après la fonction du dessus on mets une condition pour vérifier si stash est == à NULL. cela permet de prendre le cas ou le fichier est vide*/
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	return (line);
}

void	read_and_stash(int fd, t_list **stash, int *count_read_ptr)
{
	char	*buff;

	/* quand cette fonction (foundnewline) trouve un \n elle renvoie 1 et sinon un 0. Donc si cette fonction est faux on continue à rentrer dans la boucle. Count_read_ptr doit être différent de 0 car si c'est egal à 0 cela signifie qu'il y a plus rien à lire */
	while (!found_newline(*stash) && *count_read_ptr != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return ;
		/* on récupère le nombre de caractère lu par read */
		*count_read_ptr = (int)read(fd, buff, BUFFER_SIZE);
		if ((*stash == NULL && *count_read_ptr == 0) || *count_read_ptr == -1)
		{
			free(buff);
			return ;
		}
		buff[count_read_ptr] = '\0';
/* on ajoute à notre liste ce qu'il y dans le buffer */
		add_to_stash_lst(stash, buff, *count_read_ptr);
		free(buff);
	}

}

/* on ajoute ce qu'il y a dans notre buffer dans notre liste. On utilise count_read et pas BUFFER_SIZE pour avoir la bonne taille à allouer en fonction de ce que read à réellement lue */
void	add_to_stash_lst(t_list **stash, char *buff, int count_read)
{
	int	i;
	t_list	*new_last;
	t_list	*new_list;

/* avec ce malloc on initialise la liste */
	new_list = malloc(sizeof(t_list));
	if (new_list == NULL)
		return ;
/* on set up la suite de notre liste à NULL */
	new_list->next = NULL;
	new_list->content = malloc(sizeof(char) * (count_read + 1));
	if (new_list->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < count_read)
	{
		new_list->content[i] = buff[i];
		i++;
	}
	new_list->content[i] = '\0';
/* la condition ci dessous check quand on ajoute une liste pour la première fois ou stash aura plusieurs list à la suite et donc on doit ajouter la nouvelle liste à la fin */
	if (*stash == NULL)
	{
		*stash = new_list;
		return ;
	}
/* on récupère la position de la dernière liste et on ajoute la nouvelle liste à la suite de la dernière liste */
	new_last = ft_lst_last(*stash);
	new_last->next = new_list;
}

/* fonction qui extrait tous les caractères de la liste et les mets dans un string. On stoppe quand on rencontre le premier \n */

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if(stash == NULL)
		return ;
/* fonction qui va créer de la mémoire pour notre string */
	create_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
/* maintenant que notre string line a assez de mémoire grace au malloc, on vient copier les éléments qui sont dans les listes jusqu'à ce qu'on tombe sur un \n */
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				line[j++] = stash->content[i];
				break ;
			}
			line[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
}

void	clean_stash()
{
	t_list	*last;
	t_list	*clean_list;
	int	i;
	int	j;

	clean_list = malloc(sizeof(t_list));
	if (stash == NULL || clean_list == NULL)
		return ;
	clean_list->next = NULL;
	last = ft_lst_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	clean_list
}
