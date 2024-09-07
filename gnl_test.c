/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:18:51 by mirokugo          #+#    #+#             */
/*   Updated: 2024/09/08 04:18:58 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void test_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char *line;
    int line_count = 0;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Line %d: %s", ++line_count, line);
        free(line);
    }

    printf("Total lines read from %s: %d\n\n", filename, line_count);
    close(fd);
}

void test_invalid_fd() {
    char *line = get_next_line(-1);
    if (line == NULL) {
        printf("Test passed: Invalid FD returned NULL\n");
    } else {
        printf("Test failed: Invalid FD did not return NULL\n");
        free(line);
    }
}

int main() {
    // Test 1: Normal text file
    test_file("normal.txt");

    // Test 2: Empty file
    test_file("empty.txt");

    // Test 3: One line file
    test_file("one_line.txt");

    // Test 4: File with no newline at the end
    test_file("no_newline.txt");

    // Test 5: File with only newlines
    test_file("only_newlines.txt");

    // Test 6: Large file
    test_file("large_file.txt");

    // Test 7: File with binary data
    test_file("binary_file.bin");

    // Test 8: Invalid file descriptor
    test_invalid_fd();

    return 0;
}
