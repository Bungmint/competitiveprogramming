set -e
g++ ./debug/code.cpp -o code
g++ ./debug/gen.cpp -o gen
g++ ./debug/brute.cpp -o brute
g++ ./debug/checker.cpp -o checker
for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./code < input_file > myAnswer
    ./brute < input_file > correctAnswer
    ./checker > checker_log
    echo "Passed test: "  $i
done