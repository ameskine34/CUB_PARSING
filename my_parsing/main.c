/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameskine <ameskine@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:42:49 by ameskine          #+#    #+#             */
/*   Updated: 2025/12/15 15:30:14 by ameskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include "/usr/include/minilibx-linux/mlx.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_file_data
{
	t_list			*data;
	char			*n_tex;
	char			*s_tex;
	char			*w_tex;
	char			*e_tex;
	char			*f_color;
	char			*c_color;
	t_list			*map;
	char			**map_arr;
	int				ceiling_color;
	int				floor_color;
}					t_file_data;

typedef struct s_data
{
    t_file_data		*file_data;
	// t_player_data	*player_data;
	// t_game_data		*game_data;
}t_data;


static void free_split(char **arr)
{
    int i = 0;
    
    if (!arr)
        return ;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int data_alloc(t_data **data)
{   
    (*data) = malloc(sizeof(t_data));
    if (!(*data))
        return (1);
    (*data)->file_data = NULL;
	// player_data->data = NULL;
	// game_data->data = NULL;
    return (0);
}

int line_check(char *line)
{
    int i = 0;
    if (!line || line[0] == '\0')
        return (1);
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

int map_check(char *line)
{   
    if (!line || line[0] == '\0')
        return (1);
    if (ft_strnstr(line, "1",ft_strlen(line)))
        return(1);
    return (0);
}

int get_data_identifier(char *file, t_data **data)
{
    t_file_data *file_data;
    char *line;
    int fd;

    if (!data || !*data || !(*data)->file_data)
        return (printf("Error: data not allocated\n"), 1);
    file_data = (*data)->file_data;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (printf("Error opening the file\n"), 1);
    while ((line = get_next_line(fd)) != NULL)
    {
        if (!line_check(line))
        {
            ft_lstadd_back(&(file_data->data), ft_lstnew(ft_strdup(line)));
            free(line);
        }
        else
            free(line);
    }
    close(fd);
    return (0);
}

int arr_len(char **arr)
{
    int i;
    
    i = 0;
    while (arr[i])
        i++;
    return (i);
}

int check_identifier(t_file_data *file_data, char *str)
{   
    char **arr_data;
    
    arr_data = ft_split(str, ' ');
    if (!file_data || !str || !arr_data)
        return (1);
    if (arr_len(arr_data) >= 2)
    {
        if (strcmp(arr_data[0], "NO") == 0)
            file_data->n_tex = ft_strdup(arr_data[1]);
        else if (strcmp(arr_data[0], "SO") == 0)
            file_data->s_tex = ft_strdup(arr_data[1]);
        else if (strcmp(arr_data[0], "WE") == 0)
            file_data->w_tex = ft_strdup(arr_data[1]);
        else if (strcmp(arr_data[0], "EA") == 0)
            file_data->e_tex = ft_strdup(arr_data[1]);
        else if (strcmp(arr_data[0], "C") == 0)
            file_data->c_color = ft_strdup(arr_data[1]);
        else if (strcmp(arr_data[0], "F") == 0)
            file_data->f_color = ft_strdup(arr_data[1]);
        else
            return (free_split(arr_data), printf("Error: Unknown identifier\n"), 1);
    }
    free_split(arr_data);
    return (0);
}

int process_data(t_file_data *file_data)
{
    t_list *data;
    char *str;

    data = file_data->data;
    while (data)
    {
        printf("Identifier processed: %s\n", str);
        str = (char *)data->content;
        if (map_check(str))
            break;
        if (check_identifier(file_data, str))
            return (1);
        // printf("Identifier processed: %s\n", str);
        data = data->next;
    }
    return (0);
}

int file_data_alloc(t_file_data **file_data)
{
    (*file_data) = malloc (sizeof(t_file_data));
    if (!(*file_data))
        return (1);
    (*file_data)->data = NULL;
    (*file_data)->n_tex = NULL;
    (*file_data)->s_tex = NULL;
    (*file_data)->w_tex = NULL;
    (*file_data)->e_tex = NULL;
    (*file_data)->f_color = NULL;
    (*file_data)->c_color = NULL;
    (*file_data)->map = NULL;
    (*file_data)->map_arr = NULL;
    (*file_data)->ceiling_color = -1;
    (*file_data)->floor_color = -1;
    return (0);
}

int parsing(char *file, t_data **data)
{
    t_file_data *file_data;

    if (file_data_alloc(&file_data))
        return (1);
    (*data)->file_data = file_data;
    if (get_data_identifier(file, data))
        return (1);
    if (process_data(file_data))
        return (1);
    return (0);
}

int main(int ac, char **av)
{
    t_data *data;
    if (ac != 2)
        return (1);
    if (data_alloc(&data))
        return (1);
    if (parsing(av[1], &data))
        return (1);
    return (0);
}