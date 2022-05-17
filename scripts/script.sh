set -e
cd scripts
g++-11 code.cpp -o code
g++-11 gen.cpp -o gen
g++-11 brute.cpp -o brute
for ((i = 1; i <= 10000; ++i)); do
    ./gen $i >input_file
    ./code <input_file >myAnswer
    ./brute <input_file >correctAnswer
    diff -w myAnswer correctAnswer >/dev/null || break
    echo "Passed test: " $i
done
echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat myAnswer
echo "Correct answer is:"
cat correctAnswer
rm code gen brute input_file myAnswer correctAnswer
