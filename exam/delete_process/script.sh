
if [ $# -ne 2 ]; then
    echo "Invalid number of arguments"
    exit 2
fi

username=$1
filename=$2

ps -u $username -o pid,comm | grep -i "$filename" | awk '{print $1}'