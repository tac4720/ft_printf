#include "ft_printf.h"
//cspdiuxX%%

int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_putptr(void *ptr);
int	ft_putint(int n);
int	ft_putuint(unsigned int n);
int	ft_puthex(long n);
int	ft_putHex(long n);

//size_t	ft_strlen(char *str)
//{
//	size_t	i;

//	i = 0;
//	while(str[i])
//		i++;
//	return (i);
//}

//int ft_puthex_complement(int n)
//{
//	int	ret;

//	ret = 0;
//    if (n < 0)
//    {
//        unsigned int abs_val = (unsigned int)(-n); // 符号なし整数に変換して絶対値を取得
//        unsigned int complement = ~abs_val + 1;    // 1の補数を取得

//        ft_puthex(complement);
//    }
//    else
//    {
//        return (ft_puthex(n)); // 正の数の場合は通常の方法で出力
//    }
//	return (ret);
//}

//int ft_putHex_complement(int n)
//{
//	int	ret;

//	ret = 0;
//    if (n < 0)
//    {
//        unsigned int abs_val = (unsigned int)(-n); // 符号なし整数に変換して絶対値を取得
//        unsigned int complement = ~abs_val + 1;    // 1の補数を取得

//		return(ft_putHex(complement));
//    }
//    else
//    {
//        return (ft_putHex(n)); // 正の数の場合は通常の方法で出力
//    }
//	return (ret);
//}


//int	ft_putchar(int c)
//{
//	write(1, &c, 1);
//	return (1);
//}

//int	ft_putstr(char *str)
//{
//	size_t	l;

//	l = ft_strlen(str);
//	write(1, str, l);
//	return (l);
//}

//int	ft_putint(int n)
//{
//	int	count;

//	count = 0;
//	if (n == -2147483648)
//	{
//		ft_putstr("-2147483648");
//		count += 11;
//		return (count);
//	}

//	if (n < 0)
//	{
//		ft_putchar('-');
//		count++;
//		n = -n;
//	}

//	if (n >= 10)
//	{
//		count += ft_putint(n / 10);
//	}
//	ft_putchar('0' + (n % 10));
//	count++;
//	return (count);
//}

//int	ft_putuint(unsigned int n)
//{
//	int count;

//	count = 0;
//	if (n >= 10)
//	{
//		count += ft_putuint(n / 10);
//	}
//	ft_putchar('0' + (n % 10));
//	count++;
//	return(count);
//}

//int	ft_puthex(long n)
//{
//	const char	map[] = "0123456789abcdef";
//	int	count;

//	count = 0;
//	if (n >= 16)
//	{
//		count += ft_puthex(n / 16);
//	}
//	ft_putchar(map[n % 16]);
//	count++;
//	return (count);
//}

//int	ft_putHex(long n)
//{
//	const char	map[] = "0123456789ABCDEF";
//	int count;

//	count = 0;
//	if (n >= 16)
//	{
//		count += ft_putHex(n / 16);
//	}
//	ft_putchar(map[n % 16]);
//	count++;
//	return (count);
//}

//int	ft_putptr(void *ptr)
//{
//	int	count;

//	count = 0;
//	ft_putstr("0x");
//	count += 2;
//	count += ft_puthex((long)ptr);
//	return(count);
//}

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

int	ft_select(char type, va_list args)
{
	//cspdiuxX%%
	if (type == 'c')
		return ft_putchar(va_arg(args, int));
	if (type == 's')
		return ft_putstr(va_arg(args, char *));
	if (type == 'p')
		return ft_putptr(va_arg(args, void*));
	if (type == 'd')
		return ft_putint(va_arg(args, int));
	if (type == 'i')
		return ft_putint(va_arg(args, int));
	if (type == 'u')
		return ft_putuint(va_arg(args, unsigned int));
	if (type == 'x')
		return ft_puthex_complement(va_arg(args, long));
	if (type == 'X')
		return ft_putHex_complement(va_arg(args, long));
	if (type == '%')
		return ft_putchar('%');
	return (0);
}

int ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		ret;
	int		f;

	va_start(args, format);
	i = 0;
	ret = 0;
	f = 0;

	while(format[i])
	{
		if (is_fo(format[i]) && f)
		{
			ret += ft_select(format[i], args);
			f = 0;
		}
		else if (format[i] == '%')
		{
			f = 1;
		}
		else 
		{
			ft_putchar(format[i]);
			ret++;
		}
		i++;
	}

	//while(format[i])
	//{
	//	if(format[i] == '%' && is_fo(format[i + 1]))
	//	{
	//		ret += ft_select(format[i + 1], args);
	//	}
	//	else if(format[i] == '%' && is_fo(format[i + 1]) == 0)
	//	{
	//		i++;
	//		continue;
	//	}
	//	else if(is_fo(format[i]) == 0)
	//	{
	//		ft_putchar(format[i]);
	//		ret++;
	//	}
	//	else if(is_fo(format[i]) && format[i - 1] != '%')
	//	{
	//		ft_putchar(format[i]);
	//		ret++;
	//	}
	//	i++;
	//}
	va_end(args);
	return (ret);
}

//#include <stdio.h>
//int main()
//{
//	int hex;
//	int	ret;

//	ret = 0;
//	hex = 1024;

//	ret = ft_printf("%d\n", __INT_MAX__);
//	printf("%i\n", ret);

//	ret = printf("%d\n", __INT_MAX__);
//	printf("%i\n", ret);	
//}
