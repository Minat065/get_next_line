#!/bin/bash

GNL="../get_next_line.c"
GNL_UTILS="../get_next_line_utils.c"
TEST_MAIN="gnl_test.c"

CC="cc"
CFLAGS="-Wall -Wextra -Werror"
BUFFER_SIZE=32
OUTPUT="test_get_next_line"

$CC $CFLAGS -D BUFFER_SIZE=$BUFFER_SIZE $GNL $GNL_UTILS $TEST_MAIN -o $OUTPUT

VALGRIND_CMD=$(which valgrind)

if [ -z "$VALGRIND_CMD" ]; then
  echo "Valgrindがインストールされていません"
  exit 1
fi

test_cases=(
  "empty" "no_newline" "normal" "one_line" 
  "only_newlines" "learge_file"
)

for test in "${test_cases[@]}"
do
  echo "Running $test..."

  valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 \
    ./$OUTPUT "${test}.txt" > "output_${test}.txt" 2> "valgrind_${test}.txt"

  valgrind_exit_code=$?

  if diff -u "${test}.txt" "output_${test}.txt" > "diff_${test}.txt"; then
    echo "$test: 出力一致"
    rm "diff_${test}.txt"
  else
    echo "$test: 出力不一致"
    echo "Diff:"
    cat "diff_${test}.txt"
  fi

  if grep -q "All heap blocks were freed -- no leaks are possible" "valgrind_${test}.txt"; then
    echo -e "$test: メモリリークなし\n"
  else
    echo -e "$test: あーあ、メモリリークあり\n"
    echo "Valgrind log:"
    cat "valgrind_${test}.txt"
  fi

  rm "output_${test}.txt"
  rm "valgrind_${test}.txt"
done
