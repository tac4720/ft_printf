#include "ft_printf.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	size_t	l;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	l = ft_strlen(str);
	write(1, str, l);
	return (l);
}

int	ft_putint(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		count += 11;
		return (count);
	}

	if (n < 0)
	{
		ft_putchar('-');
		count++;
		n = -n;
	}

	if (n >= 10)
	{
		count += ft_putint(n / 10);
	}
	ft_putchar('0' + (n % 10));
	count++;
	return (count);
}

int	ft_putuint(unsigned int n)
{
	int count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putuint(n / 10);
	}
	ft_putchar('0' + (n % 10));
	count++;
	return(count);
}