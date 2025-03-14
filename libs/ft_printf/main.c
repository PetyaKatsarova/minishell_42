/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 12:50:21 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/11/10 14:00:25 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"

#include <stdio.h>
#include "ft_printf.h"

int main() {
    int ft_ret, orig_ret;

    // Test 1: NULL pointer
    int *ptr_null = NULL;
    ft_ret = ft_printf("ft_printf Null pointer: %p\n", (void *)ptr_null);
    orig_ret = printf("printf Null pointer: %p\n", (void *)ptr_null);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 2: Pointer to an integer
    int a = 42;
    ft_ret = ft_printf("ft_printf Pointer to integer: %p\n", (void *)&a);
    orig_ret = printf("printf Pointer to integer: %p\n", (void *)&a);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 3: Pointer to a character
    char c = 'C';
    ft_ret = ft_printf("ft_printf Pointer to char: %p\n", (void *)&c);
    orig_ret = printf("printf Pointer to char: %p\n", (void *)&c);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 4: Pointer to a double
    double d = 3.14;
    ft_ret = ft_printf("ft_printf Pointer to double: %p\n", (void *)&d);
    orig_ret = printf("printf Pointer to double: %p\n", (void *)&d);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 5: Pointer to a string
    char *str = "Hello, world!";
    ft_ret = ft_printf("ft_printf Pointer to string: %p\n", (void *)str);
    orig_ret = printf("printf Pointer to string: %p\n", (void *)str);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 6: Multiple pointers including NULL
    int b = 84;
    ft_ret = ft_printf("ft_printf Pointers: %p %p %p\n", (void *)&a, (void *)ptr_null, (void *)&b);
    orig_ret = printf("printf Pointers: %p %p %p\n", (void *)&a, (void *)ptr_null, (void *)&b);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 7: Pointer arithmetic (increment address)
    int *ptr = &a;
    ptr++;  // Point to next memory location (likely garbage)
    ft_ret = ft_printf("ft_printf Incremented pointer: %p\n", (void *)ptr);
    orig_ret = printf("printf Incremented pointer: %p\n", (void *)ptr);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 8: Print function pointer
    ft_ret = ft_printf("ft_printf Pointer to printf function: %p\n", (void *)&printf);
    orig_ret = printf("printf Pointer to printf function: %p\n", (void *)&printf);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 1: Character (%c)
    ft_ret = ft_printf("ft_printf Character: %c\n", 'Z');
    orig_ret = printf("printf Character: %c\n", 'Z');
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 2: String (%s)
    ft_ret = ft_printf("ft_printf String: %s\n", "Hello, Codam!");
    orig_ret = printf("printf String: %s\n", "Hello, Codam!");
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 3: Integer (%d)
    ft_ret = ft_printf("ft_printf Integer: %d\n", -12345);
    orig_ret = printf("printf Integer: %d\n", -12345);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 4: Unsigned Integer (%u)
    ft_ret = ft_printf("ft_printf Unsigned: %u\n", 4294967295U);
    orig_ret = printf("printf Unsigned: %u\n", 4294967295U);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 5: Hexadecimal (lowercase %x)
    ft_ret = ft_printf("ft_printf Hex (lowercase): %x\n", 3735928559U);
    orig_ret = printf("printf Hex (lowercase): %x\n", 3735928559U); // deadbeef
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 6: Hexadecimal (uppercase %X)
    ft_ret = ft_printf("ft_printf Hex (uppercase): %X\n", 3735928559U);
    orig_ret = printf("printf Hex (uppercase): %X\n", 3735928559U); // DEADBEEF
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    // Test 7: Combination of all specifiers
    ft_ret = ft_printf("ft_printf Mixed: %c %s %d %u %x %X\n", 'A', "test", -42, 42U, 0xdead, 0xBEEF);
    orig_ret = printf("printf Mixed: %c %s %d %u %x %X\n", 'A', "test", -42, 42U, 0xdead, 0xBEEF);
    printf("ft_ret: %d, orig_ret: %d\n\n", ft_ret, orig_ret);

    return 0;
}
