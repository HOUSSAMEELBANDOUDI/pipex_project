#include "pipex_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen || len == 0)
		return (ft_calloc(1, 1));
	if (slen - start <= len)
		len = slen - start; 
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		dst[i++] = s[start++];
	dst[i] = '\0';
	return (dst);
}

char	**ft_check(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

size_t	ft_countworld(char const *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
		if (str[i])
			i++;
	}
	return (count);
}

size_t	ft_len(char const *str, char c)
{
	size_t	j;

	j = 0;
	while (str[j] && str[j] != c)
		j++;
	return (j);
}

char	*ft_world(char const *str, char c)
{
	char	*dst;
	size_t	i;

	dst = (char *)malloc((ft_len(str, c) + 1) * sizeof(char));
	if (!dst)
	{
		return (NULL);
	}
	i = 0;
	while (str[i] && str[i] != c)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	j = ft_countworld(s, c);
	dst = (char **)malloc((ft_countworld(s, c) + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	i = 0;
	while (*s && i < j)
	{
		while (*s == c)
			s++;
		dst[i] = ft_world(s, c);
		if (!dst[i])
			return (ft_check(dst));
		i++;
		while (*s != c && *s)
			s++;
	}
	dst[i] = 0;
	return (dst);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	dst = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = malloc (count * size);
	if (!s)
		return (0);
	ft_bzero(s, count * size);
	return (s);
}