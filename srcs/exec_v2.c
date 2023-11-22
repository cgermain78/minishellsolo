#include "minishell.h"

void    process(t_node *node, t_data *data)
{
    int i;
    int first;
    int last;
    int input_fd;
    int output_fd;
    char *path;
    int pipe_fd[data->nb_nodes][2];
    

    last = data->nb_nodes - 1;
    i = 0;
    first = 0;
    input_fd = STDIN_FILENO;
    while(i <= last)
    {

        pipe(pipe_fd[i]);
        if (fork() == 0)
        {
            path = ft_strdup("/bin/");
            ft_strlcat(path, node->str_options[0], 1000);
            if(node->fd_in != 0)
                input_fd = node->fd_in;
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
            if(node->fd_out > 1)
                output_fd = node->fd_out;
            else
                output_fd = pipe_fd[i][1];
            if(i != last || (i == last && node->fd_out > 1))
            {
                dup2(output_fd, STDOUT_FILENO);
                close(pipe_fd[i][0]);
                close(pipe_fd[i][1]);
            }
            execve(path, node->str_options, list_to_tab(data->envp));
        }
        if(i != first)
            close(input_fd);
        if (i != last)
        {
            close(pipe_fd[i][1]);
            input_fd = dup(pipe_fd[i][0]);
            close(pipe_fd[i][0]);
        }
        i++;
        node = node->next;
        wait(NULL);
    }
}
