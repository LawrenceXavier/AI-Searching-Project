# Remove old files
if [ -f main ]; then
	rm -f main
fi


# Compile project
echo "Compiling..." 

g++ -g -O2 -std=gnu++14 -static -o main main.cpp 

echo "Finished compiling"


# Run project

if [ -f main ]; then
	echo "Running..."

	./main

	echo "Finished running"
else 
	echo "Program does not exist"
fi
