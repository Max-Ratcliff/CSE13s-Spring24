# Runs the program with a too small first input
out=$(./calc 4 -513) #caputers output to variable
code=$? #saves exit code to variable
expected="TOO BIG" #

# Ensures exit code is not Zero
if [ $code -eq 0 ]; then
    echo "failed to detect \"TOO BIG\": $code"
    exit 1
fi

# Ensures "TOO BIG" is printed
if [[ ! "$out" =~ "$expected" ]]; then
    echo "failed to print \"TOO BIG\""
    exit 1
fi

# Ensures output ends in a newline
if [[ ! "$out" =~ $'\n'$ ]]; then
    echo "does not end in newline"
    exit 1
fi


# Prints a message on success
echo "properly handles inputs: PASS"
exit 0


