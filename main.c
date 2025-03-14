/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 11:17:10 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/03/14 17:01:08 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

// cc -Wall -Wextra -Werror main.c -lreadline && ./a.out

int main() {
    char *input = readline("tra la la: ");
    if (input && *input) { // Ensure input is not NULL or empty
        add_history(input); // Store input in history
        printf("You entered: %s\n", input);
        free(input);
    }
    return 0;
}