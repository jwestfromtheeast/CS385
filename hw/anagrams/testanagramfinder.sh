#!/bin/bash

file=anagramfinder.cpp

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
        interpreter=$(which python3.6)
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

run_test_args() {
    (( ++total ))
    echo -n "Running test $total..."
    expected=$2
    received=$( $command $1 2>&1 | tr -d '\r' )
    if [ "$expected" = "$received" ]; then
        echo "success"
        (( ++num_right ))
    else
        echo -e "failure\n\nExpected$line\n$expected\nReceived$line\n$received\n"
    fi
}

run_test_args "" "Usage: ./anagramfinder <dictionary file>"
run_test_args "file1.txt file2.txt" "Usage: ./anagramfinder <dictionary file>"
run_test_args "nofile.txt" "Error: File 'nofile.txt' not found."

(cat << EOF
EOF
) > words.txt
run_test_args "words.txt" "No anagrams found."
rm -f words.txt

(cat << EOF
a
b
c
d
aa
bb
cc
dd
EOF
) > words.txt
run_test_args "words.txt" "No anagrams found."
rm -f words.txt

(cat << EOF
a
b
c
a
c
d
EOF
) > words.txt
run_test_args "words.txt" "Max anagrams: 2"$'\n'"a"$'\n'"a"$'\n'$'\n'"c"$'\n'"c"
rm -f words.txt

(cat << EOF
tea
home
eat
ate
react
trace
EOF
) > words.txt
run_test_args "words.txt" "Max anagrams: 3"$'\n'"ate"$'\n'"eat"$'\n'"tea"
rm -f words.txt

(cat << EOF
cater
tea
home
eat
ate
react
trace
EOF
) > words.txt
run_test_args "words.txt" "Max anagrams: 3"$'\n'"ate"$'\n'"eat"$'\n'"tea"$'\n'$'\n'"cater"$'\n'"react"$'\n'"trace"
rm -f words.txt

(cat << EOF
CATER
tea
home
eat
ate
REACT
trace
EOF
) > words.txt
run_test_args "words.txt" "Max anagrams: 3"$'\n'"CATER"$'\n'"REACT"$'\n'"trace"$'\n'$'\n'"ate"$'\n'"eat"$'\n'"tea"
rm -f words.txt

(cat << EOF
pots
stop
tops
a
b
c
eat
ate
trace
tea
d
e
f
react
cater
EOF
) > words.txt
run_test_args "words.txt" "Max anagrams: 3"$'\n'"ate"$'\n'"eat"$'\n'"tea"$'\n'$'\n'"cater"$'\n'"react"$'\n'"trace"$'\n'$'\n'"pots"$'\n'"stop"$'\n'"tops"
rm -f words.txt

echo -e "\nTotal tests run: $total"
echo -e "Number correct : $num_right"
echo -n "Percent correct: "
echo "scale=2; 100 * $num_right / $total" | bc

if [ "$language" = "java" ]; then
    echo -e -n "\nRemoving class files..."
    rm -f *.class
    echo "done"
elif [ $language = "c" ]; then
    echo -e -n "\nCleaning project..."
    make clean > /dev/null 2>&1
    echo "done"
fi
