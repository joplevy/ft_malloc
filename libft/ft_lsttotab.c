#include "libft.h"

char	**ft_lsttotab(t_list	*list)
{
	char	**tab;
	int		len;
	int		i;
	t_list	*ptr;

	ptr = list;
	i = 0;
	ft_putstr("test");
	len = ft_lstlen(list);
	tab = malloc((len + 1) * sizeof(char **));
	while(ptr->next)
	{
		tab[i] = ft_strdup(ptr->content);
		i++;
		tab[i] = NULL;
		ptr = ptr->next;
	}
	return(tab);
}
