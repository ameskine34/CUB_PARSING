/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameskine <ameskine@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:42:49 by ameskine          #+#    #+#             */
/*   Updated: 2025/12/22 17:17:39 by ameskine         ###   ########.fr       */
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

int white_spaces(char *line)
{
    int i = 0;
    int j = 0;
    while (line[i])
    {
        if (line[j] == ' ' || line[j] == '\t')
            j++;
        i++;
    }
    return (j);
}

int map_check(char *line)
{   
    if (!line || line[0] == '\0')
        return (1);
    // if (ft_strnstr(line, "1",1))
    //     return(0);
    int i = white_spaces(line);
    if (line[i] == '\0') 
        return (1); 
    if (line[i] != '1')
        return (printf("Error: Map not starting with 1\n"), 1);
    return (1);
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
    if (!file_data || !arr_data || str[0] == '1')
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
            return (free_split(arr_data), 1);
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
        str = (char *)data->content;
        if (check_identifier(file_data, str))
        {
            if (!map_check(str))
            {
                while (data)
                {
                    ft_lstadd_back(&(file_data->map), ft_lstnew(ft_strtrim((char *)data->content, "\n")));
                    data = data->next;
                }
                return (0);
            }
        }
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

int check_dup(char c)
{
    static int flags[256] = {0};
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        if (flags[(unsigned char)c])
            return (1);
        flags[(unsigned char)c] = 1;
    }
    return (0);
}

int invalid_char_in_line(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
            return (1);
        if (check_dup(line[i]))
            return (1);
        i++;
    }
    return (0);
}

int invalid_hf_line(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ')       
            return (1);
        i++;
    }
    return (0);
}

int invalid_extreme_line(char *line)
{
    int i = 0;
    int len;

    len = ft_strlen(line);
    if (line[0] != '1' && line[0] != ' ')
        return (1);
    if (line[len - 1] != '1' && line[len - 1] != ' ')
        return (1);
    return (0);
}

int check_valid_map(t_file_data *file_data)
{
    t_list *map;
    char *line;
    int i;

    map = file_data->map;
    line = (char *)map->content;
    if (!map)
        return (printf("Error: Map is empty\n"), 1);
    if (ft_lstsize(map) < 3)
        return (printf("Error: Map is too small\n"), 1);
    if (invalid_hf_line(line))
        return (printf("Error: Invalid first line in map\n"), 1);
    if (invalid_hf_line((char *)ft_lstlast(map)->content))
        return (printf("Error: Invalid last line in map\n"), 1);
    while (map)
    {   
        i = 0;
        line = (char *)map->content;
        if (invalid_char_in_line(line))
            return (printf("Error: Invalid character in map or dup \n"), 1);
        if (invalid_extreme_line(line))
            return (printf("Error: Invalid extreme line in map\n"), 1);
        map = map->next;
    }
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
    if (!file_data->n_tex || !file_data->s_tex || !file_data->w_tex || !file_data->e_tex
        || !file_data->f_color || !file_data->c_color)
    {
        return (printf("Error: Missing identifiers \n"), 1);
    }
    if (check_valid_map(file_data))
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