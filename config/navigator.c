/*
** navigator.c for navigator in /home/arthur/Documents/Sock
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sat Apr 22 15:20:13 2017 Arthur Knoepflin
** Last update Sun May 21 04:07:39 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "server.h"
#include "shell.h"
#include "my.h"

static char	**get_path(char **ae)
{
  char		*tmp;
  char		**ret;

  if ((ret = malloc(sizeof(char *) * 3)) == NULL)
    return (NULL);
  ret[2] = NULL;
  ret[0] = my_strdup("/bin");
  ret[1] = my_strdup("/usr/bin");
  if (!ae)
    return (ret);
  if ((tmp = get_env("PATH")) == NULL)
    return (ret);
  free_tab(ret);
  return (my_split(tmp, ":"));
}

static char	*test_access(char *tmp)
{
  char		*ret;

  ret = my_strcatdup(tmp, CHROME);
  if (access(ret, X_OK) == 0)
    {
      free(tmp);
      return (ret);
    }
  free(ret);
  ret = my_strcatdup(tmp, FIREFOX);
  if (access(ret, X_OK) == 0)
    {
      free(tmp);
      return (ret);
    }
  free(ret);
  return (NULL);
}

char	*find_navigator(char **ae)
{
  char	*tmp;
  char	*ret;
  char	**path;
  int	i;

  if ((path = get_path(ae)) == NULL)
    return (NULL);
  i = 0;
  while (path[i])
    {
      if (path[i][my_strlen(path[i]) - 1] != '/')
      	tmp = my_strcatdup(path[i], "/");
      else
      	tmp = my_strdup(path[i]);
      if ((ret = test_access(tmp)) != NULL)
	{
	  free_tab(path);
	  return (ret);
	}
      free(tmp);
      i += 1;
    }
  free_tab(path);
  return (NULL);
}

static int	dup_child(void)
{
  int		fd;

  if ((fd = open("/dev/null", O_RDONLY)) == -1)
    return (1);
  dup2(fd, 1);
  dup2(fd, 2);
  close(fd);
  return (0);
}

int	launch_nav(char *path, int port, char **ae)
{
  int	pid;
  char	**argv;

  if ((argv = malloc(sizeof(char *) * 3)) == NULL)
    return (1);
  argv[2] = NULL;
  argv[0] = path;
  argv[1] = my_strdup(PATH_WEB);
  argv[1] = my_fstrcat(argv[1], int_toc(port), 2);
  if ((pid = fork()) == 0)
    {
      dup_child();
      execve(path, argv, ae);
      free_tab(argv);
      exit(0);
    }
  free_tab(argv);
  return (0);
}
