#!/bin/bash

MINISHELL=./minishell
ERROR_LOG=errors.log
TEST_COUNT=0
PASS_COUNT=0

# Clean old log
> $ERROR_LOG

# Define tests: each line is "command | expected_output"
read -r -d '' TESTS << EOM
"echo hello" "hello"
"echo hello | grep h" "hello"
"echo hello | grep x" ""
"ls / | grep bin" "bin"
"pwd | grep /" "/"
"echo test | cat" "test"
"echo test | cat | grep t" "test"
"env | grep PATH" "PATH"
"export TESTVAR=ok && echo \$TESTVAR" "ok"
"unset TESTVAR && echo \$TESTVAR" ""
"echo first | grep first | cat" "first"
"echo second | cat | grep sec" "second"
"which ls | grep bin" "bin"
"echo one two | grep one" "one two"
"echo test | grep -v x" "test"
"echo foo | grep bar" ""
"cd /tmp && pwd | grep /tmp" "/tmp"
"echo 123 | grep 1 | grep 2 | grep 3" "123"
"echo abc | tr a-z A-Z" "ABC"
"echo done | grep done | cat | grep d" "done"
EOM

# Run all tests
while IFS= read -r line; do
    CMD=$(echo "$line" | cut -d '"' -f2)
    EXPECTED=$(echo "$line" | cut -d '"' -f4)

    OUTPUT=$(printf "%s\nexit\n" "$CMD" | $MINISHELL 2>/dev/null | tr -d '\r')
    TEST_COUNT=$((TEST_COUNT+1))

    if [[ "$OUTPUT" == *"$EXPECTED"* ]]; then
        PASS_COUNT=$((PASS_COUNT+1))
    else
        echo "FAILED: '$CMD' → Got: '$OUTPUT' | Expected: '$EXPECTED'" >> $ERROR_LOG
    fi
done <<< "$TESTS"

# Summary
echo "$PASS_COUNT / $TEST_COUNT tests passed."
if [ $PASS_COUNT -ne $TEST_COUNT ]; then
    echo "Errors logged in $ERROR_LOG"
fi
