year=2025
day=$1
numInputs=${2:-2}

if [ -z "$year" ] || [ -z "$day" ]; then
    echo "Usage: ./create-day-template.sh <day> [numInputs]"
    exit 1
fi

if [ ! -f template.cpp ]; then
    echo "Error: template.cpp not found in the current directory."
    exit 1
fi

# pth="./$year/d$day"
pth="./d$day"
mkdir -p $pth

dest="$pth/solution.cpp"
if [ -f "$dest" ]; then
    echo "Notice: $dest exists — not overwriting."
else
    cp template.cpp $dest
fi

mkdir $pth/part1
mkdir $pth/part2
for i in $(seq 1 $numInputs); do
    touch $pth/$i.in.txt
    touch $pth/part1/$i-p1.exp.txt
    touch $pth/part2/$i-p2.exp.txt
done