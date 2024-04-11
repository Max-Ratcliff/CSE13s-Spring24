# Runs the program with a too small first input
./calc -513 4 > out.txt 

# Ensures exit code is not Zero
if [ $? -eq 0 ]; then
    echo "failed to detect \"TOO BIG\"" $?
    rm out.txt
    exit 1
fi

# Ensures "TOO BIG" is printed
Last = tail -1 out.txt
echo Last
if [ Last  -ne  "TOO BIG" ]; then
    echo "failed to print \"TOO BIG\""
    rm out.txt
    exit 1
fi

# Runs the program with a too big first input
./calc 513 4 > out.txt 

# Ensures exit code is not Zero
if [ $? -eq 0 ]; then
    echo "failed to detect \"TOO BIG\"" $?
    rm out.txt
    exit 1
fi

# Ensures "TOO BIG" is printed
Last = tail -1 out.txt
echo Last
if [ Last  -ne  "TOO BIG" ]; then
    echo "failed to print \"TOO BIG\""
    rm out.txt
    exit 1
fi


# Runs the program with a too small second input
./calc 4 -513 > out.txt 

# Ensures exit code is not Zero
if [ $? -eq 0 ]; then
    echo "failed to detect \"TOO BIG\"" $?
    rm out.txt
    exit 1
fi

# Ensures "TOO BIG" is printed
Last = tail -1 out.txt
echo Last
if [ Last  -ne  "TOO BIG" ]; then
    echo "failed to print \"TOO BIG\""
    rm out.txt
    exit 1
fi

# Runs the program with a too big second input
./calc 4 513 > out.txt 

# Ensures exit code is not Zero
if [ $? -eq 0 ]; then
    echo "failed to detect \"TOO BIG\"" $?
    rm out.txt
    exit 1
fi

# Ensures "TOO BIG" is printed
Last = tail -1 out.txt
echo Last
if [ Last  -ne  "TOO BIG" ]; then
    echo "failed to print \"TOO BIG\""
    rm out.txt
    exit 1
fi

# Runs the program with two too small inputs
./calc -513 -513 > out.txt 

# Ensures exit code is not Zero
if [ $? -eq 0 ]; then
    echo "failed to detect \"TOO BIG\"" $?
    rm out.txt
    exit 1
fi

# Ensures "TOO BIG" is printed
Last = tail -1 out.txt
echo Last
if [ Last  -ne  "TOO BIG" ]; then
    echo "failed to print \"TOO BIG\""
    rm out.txt
    exit 1
fi

# Runs the program with two too big inputs
./calc 513 513 > out.txt 

# Ensures exit code is not Zero
if [ $? -eq 0 ]; then
    echo "failed to detect \"TOO BIG\"" $?
    rm out.txt
    exit 1
fi

# Ensures "TOO BIG" is printed
Last = tail -1 out.txt
echo Last
if [ Last  -ne  "TOO BIG" ]; then
    echo "failed to print \"TOO BIG\""
    rm out.txt
    exit 1
fi


# Prints a message on success
echo "properly handles too big inputs: PASS"

# Cleans up files created
rm out.txt
exit 0


