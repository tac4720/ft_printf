#include "ft_printf.h"

int ft_puthex_complement(int n)
{
	int	ret;
	
	ret = 0;
    if (n < 0)
    {
        unsigned int abs_val = (unsigned int)(-n); // 符号なし整数に変換して絶対値を取得
        unsigned int complement = ~abs_val + 1;    // 1の補数を取得

        return (ft_puthex(complement));
    }
    else
    {
        return (ft_puthex(n)); // 正の数の場合は通常の方法で出力
    }
	return (ret);
}

int ft_putHex_complement(int n)
{
	int	ret;

	ret = 0;
    if (n < 0)
    {
        unsigned int abs_val = (unsigned int)(-n); // 符号なし整数に変換して絶対値を取得
        unsigned int complement = ~abs_val + 1;    // 1の補数を取得

		return(ft_putHex(complement));
    }
    else
    {
        return (ft_putHex(n)); // 正の数の場合は通常の方法で出力
    }
	return (ret);
}

int	ft_puthex(long n)
{
	const char	map[] = "0123456789abcdef";
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_puthex(n / 16);
	}
	ft_putchar(map[n % 16]);
	count++;
	return (count);
}

int	ft_putHex(long n)
{
	const char	map[] = "0123456789ABCDEF";
	int count;

	count = 0;
	if (n >= 16)
	{
		count += ft_putHex(n / 16);
	}
	ft_putchar(map[n % 16]);
	count++;
	return (count);
}

int	ft_putptr(void *ptr)
{
	int	count;

	count = 0;
	ft_putstr("0x");
	count += 2;
	count += ft_puthex((long)ptr);
	return(count);
}