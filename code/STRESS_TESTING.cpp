set -e
g++ -std=c++17 gen.cpp -o gen
g++ -std=c++17 main.cpp -o main
g++ -std=c++17 brute.cpp -o brute
for((i = 1; ; ++i)); do
  echo $i
  ./gen $i > in
  ./main < in > out
  ./brute < in > out2
  diff -w out out2 || break
done