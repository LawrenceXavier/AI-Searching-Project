echo "Removing output files"

if [ -f core ]; then
	echo "Removing core"
	rm core
fi

if [ -f main ]; then
	echo "Removing main"
	rm main
fi

if [ -f dfs.txt ]; then
	echo "Removing dfs.txt"
	rm dfs.txt
fi

if [ -f bfs.txt ]; then
	echo "Removing bfs.txt"
	rm bfs.txt
fi

if [ -f ucs.txt ]; then
	echo "Removing ucs.txt"
	rm ucs.txt
fi

if [ -f gbfs.txt ]; then
	echo "Removing gbfs.txt"
	rm gbfs.txt
fi

if [ -f astar.txt ]; then
	echo "Removing astar.txt"
	rm aster.txt
fi
