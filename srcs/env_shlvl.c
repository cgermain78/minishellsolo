/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:53:44 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/03 15:53:50 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	manage_shlvl(char *env, char **result, int j)
{
	int		nb;
	int		i;
	char	*number;

	i = 0;
	nb = ft_atoi(&env[6]);
	nb++;
	number = ft_itoa(nb);
	result[j] = malloc(sizeof(char) * (7 + ft_strlen(number)));
	if (!result)
		return ;
	while (i < 6)
	{
		result[j][i] = env[i];
		i++;
	}
	while (number[i - 6])
	{
		result[j][i] = number[i - 6];
		i++;
	}
	free(number);
	result[j][i] = '\0';
}

char	*manage_pwd(void)
{
	char	str[256];
	char	cwd[256];

	str[0] = 'P';
	str[1] = 'W';
	str[2] = 'D';
	str[3] = '=';
	str[4] = '\0';
	getcwd(cwd, sizeof(cwd));
	ft_strlcat(str, cwd, 256);
	return (ft_strdup(str));
}

char	**create_envp(void)
{
	char	**envp;

	envp = malloc(sizeof(char *) * 3);
	if (!envp)
		return (NULL);
	envp[0] = manage_pwd();
	envp[1] = ft_strdup("SHLVL=1");
	envp[2] = NULL;
	return (envp);
}
