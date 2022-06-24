set -e
cd scripts
g++-11 code.cpp -o code
g++-11 gen.cpp -o gen
g++-11 brute.cpp -o brute
g++-11 checker.cpp -o checker
for((i = 1; i <= 10000; ++i)); do
    ./gen $i > input_file
    ./code < input_file > myAnswer
    ./brute < input_file > correctAnswer
    ./checker > checker_log || break
    echo "Passed test: "  $i
done
echo "Failed on the following test case:"
cat input_file
echo "Your answer is:"
cat myAnswer
echo "Checker log:"
cat checker_log
rm code gen brute input_file myAnswer correctAnswer checker checker_log