#include "libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*make_word(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (ft_substr(s, 0, len));
}

static void	free_words(char **tab, size_t i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;

	if (!s)
		return (NULL);
	tab = ft_calloc(word_count(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			tab[i] = make_word(s, c);
			if (!tab[i])
				return (free_words(tab, i), NULL);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	return (tab);
}
