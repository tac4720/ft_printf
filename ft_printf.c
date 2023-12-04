#include "ft_printf.h"
//cspdiuxX%%

void	ft_putchar(int c);
void	ft_putstr(char *str);
void	ft_putptr(void *ptr);
void	ft_putint(int n);
void	ft_putuint(unsigned int n);
void	ft_puthex(long n);
void	ft_putHex(long n);

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void ft_puthex_complement(int n)
{
    const char map[] = "0123456789abcdef";

    if (n < 0)
    {
        unsigned int abs_val = (unsigned int)(-n); // 符号なし整数に変換して絶対値を取得
        unsigned int complement = ~abs_val + 1;    // 1の補数を取得

        for (int i = sizeof(unsigned int) * 8 - 4; i >= 0; i -= 4)
        {
            int index = (complement >> i) & 0xF;
            ft_putchar(map[index]);
        }
    }
    else
    {
        ft_puthex(n); // 正の数の場合は通常の方法で出力
    }
}

void ft_putHex_complement(int n)
{
	const char map[] = "0123456789ABCDEF";

    if (n < 0)
    {
        unsigned int abs_val = (unsigned int)(-n); // 符号なし整数に変換して絶対値を取得
        unsigned int complement = ~abs_val + 1;    // 1の補数を取得

        for (int i = sizeof(unsigned int) * 8 - 4; i >= 0; i -= 4)
        {
            int index = (complement >> i) & 0xF;
            ft_putchar(map[index]);
        }
    }
    else
    {
        ft_putHex(n); // 正の数の場合は通常の方法で出力
    }
}


void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	size_t	l;

	l = ft_strlen(str);
	write(1, str, l);
}

void	ft_putint(int n)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}

	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}

	if (n >= 10)
	{
		ft_putint(n / 10);
	}
	ft_putchar('0' + (n % 10));
}

void	ft_putuint(unsigned int n)
{
	if (n >= 10)
	{
		ft_putuint(n / 10);
	}
	ft_putchar('0' + (n % 10));
}

void	ft_puthex(long n)
{
	const char	map[] = "0123456789abcdef";

	if (n >= 16)
	{
		ft_puthex(n / 16);
	}
	ft_putchar(map[n % 16]);
}

void	ft_putHex(long n)
{
	const char	map[] = "0123456789ABCDEF";

	if (n >= 16)
	{
		ft_putHex(n / 16);
	}
	ft_putchar(map[n % 16]);
}

void	ft_putptr(void *ptr)
{
	ft_putstr("0x");
	ft_puthex((long)ptr);
}

int	is_fo(int c)
{
	size_t				i;
	const unsigned char	f_list[] = "cspdiuxX%%";

	i = 0;
	while (f_list[i])
	{
		if ((unsigned char)c == f_list[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_select(char type, va_list args)
{
	//cspdiuxX%%
	if (type == 'c')
		ft_putchar(va_arg(args, int));
	if (type == 's')
		ft_putstr(va_arg(args, char *));
	if (type == 'p')
		ft_putptr(va_arg(args, void *));
	if (type == 'd')
		ft_putint(va_arg(args, int));
	if (type == 'i')
		ft_putint(va_arg(args, int));
	if (type == 'u')
		ft_putuint(va_arg(args, unsigned int));
	if (type == 'x')
		ft_puthex_complement(va_arg(args, long));
	if (type == 'X')
		ft_putHex_complement(va_arg(args, long));
	if (type == '%')
		putchar('%');
}

ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;

	va_start(args, format);
	i = 0;

	while(format[i])
	{
		if(format[i] == '%' && is_fo(format[i + 1]))
		{
			ft_select(format[i + 1], args);
		}
		else if(format[i] == '%' && is_fo(format[i + 1]) == 0)
		{
			i++;
			continue;
		}	
		else if(is_fo(format[i]) == 0)
		{
			ft_putchar(format[i]);
		}
		i++;
	}
}

int main(void)
{
	int hex;

	hex = -1024;

	ft_printf("%x", hex);
	ft_putchar('\n');
	printf("%x", hex);
}
