/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:11:23 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/22 00:34:57 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_split_result(char **result)
{
    if (!result)
    {
        printf("Result is NULL\n");
        return;
    }
    printf("Result tokens:\n");
    for (int i = 0; result[i] != NULL; i++)
    {
        // [] で囲むことで、末尾に改行やスペースが残っていないか確認
        printf("  index [%d] : [%s]\n", i, result[i]);
    }
    printf("--------------------------\n");
}

int main(void)
{
    char **result;

    // テスト1: 標準的なケース
    printf("Test 1: Standard space\n");
    result = ft_split("L 0,0,0 0.5 255,255,255", ' ');
    print_split_result(result);
    ft_free_tab(result);

    // テスト2: 連続するスペース（これどうか？）
    printf("Test 2: Multiple spaces (A  0.2)\n");
    result = ft_split("A  0.2  255,255,255", ' ');
    print_split_result(result);
    ft_free_tab(result);

    // テスト3: 行末の改行を切り取れるのか（GNLに対策必要？）
    printf("Test 3: Newline at the end (from GNL)\n");
    result = ft_split("C 0,0,0 0,0,1 70\n", ' ');
    print_split_result(result);
    ft_free_tab(result);

    // テスト4: タブが含まれる場合はどうか（isspace対策が必要か？）
    printf("Test 4: Tab character instead of space\n");
    result = ft_split("sp\t0,0,20\t10\t255,0,0", ' ');
    print_split_result(result);
    ft_free_tab(result);

    // テスト5: 空文字列はどうか？
    printf("Test 5: Empty string\n");
    result = ft_split("", ' ');
    print_split_result(result);
    ft_free_tab(result);
    return (0);
}
