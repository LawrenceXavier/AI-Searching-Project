# Remove old files
if [ -f main ]; then
	rm -f main
fi


# Compile project
echo "Compiling..." 

g++ -g -O2 -std=gnu++14 -static -o main Geometry.cpp AllObject.cpp PrintCanvas.cpp FindPath.cpp main.cpp

echo "Finished compiling"


# Run project

if [ -f main ]; then
	echo "Running..."

	./main

	echo "Finished running"

	if [ -f Output.html ]; then
		read -p "Do you want to open the demo in browser? " -n 1 -r
		echo # make a blank line 	
		if [[ $REPLY =~ ^[Yy]$ ]] 
		then
			    xdg-open Output.html
		fi

	fi
else 
	echo "Program does not exist"
fi
