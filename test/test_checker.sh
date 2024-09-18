#!/bin/bash

# コンパイル

GNL="../get_next_line.c"
GNL_UTILS="../get_next_line_utils.c"
TEST_MAIN="gnl_test.c"

CC="cc"
CFLAGS="-Wall -Wextra -Werror"
BUFFER_SIZE=32
OUTPUT="test_get_next_line"

#コンパイルの実行
$CC $CFLAGS -D BUFFER_SIZE=$BUFFER_SIZE $GNL $GNL_UTILS $TEST_MAIN -o $OUTPUT

# Valgrindのパス（必要に応じて修正）
VALGRIND_CMD=$(which valgrind)

# Valgrindがインストールされているか確認
if [ -z "$VALGRIND_CMD" ]; then
  echo "Valgrindがインストールされていません。インストールしてください。"
  exit 1
fi

# テストケースの配列
test_cases=( 
  "empty" "no_newline" "normal" "one_line" 
  "only_newlines"
)

# すべてのテストケースをループ
for test in "${test_cases[@]}"
do
  echo "Running $test..."

  # Valgrindを使用してテストを実行し、メモリリークをチェック
  valgrind --leak-check=full --error-exitcode=1 \
    ./$OUTPUT < "${test}.txt" > "output_${test}.txt" 2> "valgrind_${test}.txt"

  # Valgrindの終了コードを取得
  valgrind_exit_code=$?

  # 出力を比較
  if diff -q "output_${test}.txt" "${test}.txt" > /dev/null; then
    echo "$test: 出力一致"
  else
    echo "$test: 出力不一致"
    echo "差分:"
    diff "output_${test}.txt" "${test}.txt"
  fi

  # メモリリークの結果を確認
  if [ $valgrind_exit_code -eq 0 ]; then
    echo "$test: メモリリークなし"
  else
    echo "$test: メモリリーク検出"
    echo "Valgrindログ:"
    cat "valgrind_${test}.txt"
  fi

  # 一時ファイルを削除
  rm "output_${test}.txt"
  rm "valgrind_${test}.txt"

done  
