

if [ $# -ne 1 ]; then
    echo "Number of arguments invalid. Provide just a string"
    exit 1
fi

sentence=$1

IFS="a"
for word in $sentence; do
    echo "$word"
done