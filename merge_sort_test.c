/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   merge_sort_test.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 19:28:02 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 19:37:44 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void    merge_sort(void *t, size_t esize, int length, int (*cmp)(void*,void*));

/*

void	print_result(int a[], int len)
{
	int	i = 0;

	while (i < len - 1)
		printf("%d, ", a[i++]);
	if (i < len)
		printf("%d\n", a[i]);
	else
		printf("\n");
}
*/
int		cmp(void *a, void *b)
{
	return (*(int*)a > *(int*)b ? 1 : 0);
}

int		sorted(int a[], int len)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (a[i] > a[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int		main(int ac, char *av[])
{
	int		array[100000];
	int		copy[100000];
	int		i = 0;
	int		max;
	int		result[2] = {0};
	
	if (ac == 1)
		max = 101;
	else
		max = atoi(av[1]);
	if (max > 99999)
		max = 99999;
	srand(time(NULL));
	while (i < max)
		array[i++] = (rand() % 0xff) - (0xff / 2);
	i = 0;
	while (i <= max)
	{
		if (i)
			memcpy(copy, array, i * sizeof(int));
		merge_sort(copy, sizeof(int), i, cmp);
	//	print_result(copy, i);
		if (!sorted(copy, i))
			result[0]++;
//			printf("\e[0;31mtest %d failed\e[0m\n", i);
		else
			result[1]++;
//			printf("\e[0;32mtest %d success\e[0m\n", i);
		i++;
	}
	printf("\e[0;32m%d tests success\e[0m, \e[0;31m%d tests failed\e[0m\n\n", result[1], result[0]);
}
