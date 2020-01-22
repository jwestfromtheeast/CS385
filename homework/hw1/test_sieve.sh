#!/bin/bash

file=sieve.cpp

if [ ! -f "$file" ]; then
    echo -e "Error: File '$file' not found.\nTest failed."
    exit 1
fi

num_right=0
total=0
line="________________________________________________________________________"
compiler=
interpreter=
language=
extension=${file##*.}
if [ "$extension" = "py" ]; then
    if [ ! -z "$PYTHON_PATH" ]; then
        interpreter=$(which python.exe)
    else
        interpreter=$(which python3.2)
    fi
    command="$interpreter $file"
    echo -e "Testing $file\n"
elif [ "$extension" = "java" ]; then
    language="java"
    command="java ${file%.java}"
    echo -n "Compiling $file..."
    javac $file
    echo -e "done\n"
elif [ "$extension" = "c" ] || [ "$extension" = "cpp" ]; then
    language="c"
    command="./${file%.*}"
    echo -n "Compiling $file..."
    results=$(make 2>&1)
    if [ $? -ne 0 ]; then
        echo -e "\n$results"
        exit 1
    fi
    echo -e "done\n"
fi

run_test() {
    (( ++total ))
    echo -n "Running test $total..."
    expected=$2
    received=$( echo -e $1 | $command 2>&1 | tr -d '\r' )
    if [ "$expected" = "$received" ]; then
        echo "success"
        (( ++num_right ))
    else
        echo -e "failure\n\nExpected$line\n$expected\nReceived$line\n$received\n"
    fi
}

run_test "x" "**************************** Sieve of Eratosthenes ****************************"$'\n'"Search for primes up to: Error: Input is not an integer."
run_test "-1" "**************************** Sieve of Eratosthenes ****************************"$'\n'"Search for primes up to: Error: Input must be an integer >= 2."
run_test "0" "**************************** Sieve of Eratosthenes ****************************"$'\n'"Search for primes up to: Error: Input must be an integer >= 2."
run_test "1" "**************************** Sieve of Eratosthenes ****************************"$'\n'"Search for primes up to: Error: Input must be an integer >= 2."
run_test "2" "**************************** Sieve of Eratosthenes ****************************"$'\n'"Search for primes up to: "$'\n'"Number of primes found: 1"$'\n'"Primes up to 2:"$'\n'"2"
run_test "10" "**************************** Sieve of Eratosthenes ****************************"$'\n'"Search for primes up to: "$'\n'"Number of primes found: 4"$'\n'"Primes up to 10:"$'\n'"2 3 5 7"
run_test "99" "**************************** Sieve of Eratosthenes ****************************"$'\n'"Search for primes up to: "$'\n'"Number of primes found: 25"$'\n'"Primes up to 99:"$'\n'"2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97"
run_test "173" "**************************** Sieve of Eratosthenes ****************************"$'\n'"Search for primes up to: "$'\n'"Number of primes found: 40"$'\n'"Primes up to 173:"$'\n'"  2   3   5   7  11  13  17  19  23  29  31  37  41  43  47  53  59  61  67  71"$'\n'" 73  79  83  89  97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173"
run_test "250" "**************************** Sieve of Eratosthenes ****************************"$'\n'"Search for primes up to: "$'\n'"Number of primes found: 53"$'\n'"Primes up to 250:"$'\n'"  2   3   5   7  11  13  17  19  23  29  31  37  41  43  47  53  59  61  67  71"$'\n'" 73  79  83  89  97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173"$'\n'"179 181 191 193 197 199 211 223 227 229 233 239 241"
run_test "1000" "**************************** Sieve of Eratosthenes ****************************"$'\n'"Search for primes up to: "$'\n'"Number of primes found: 168"$'\n'"Primes up to 1000:"$'\n'"  2   3   5   7  11  13  17  19  23  29  31  37  41  43  47  53  59  61  67  71"$'\n'" 73  79  83  89  97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173"$'\n'"179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281"$'\n'"283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409"$'\n'"419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541"$'\n'"547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659"$'\n'"661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809"$'\n'"811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941"$'\n'"947 953 967 971 977 983 991 997"

echo -e "\nTotal tests run: $total"
echo -e "Number correct : $num_right"
echo -n "Percent correct: "
echo "scale=2; 100 * $num_right / $total" | bc

if [ "$language" = "java" ]; then
    echo -e -n "\nRemoving class files..."
    rm -f *.class
    echo "done"
elif [ "$language" = "c" ]; then
    echo -e -n "\nCleaning project..."
    make clean > /dev/null 2>&1
    echo "done"
fi
