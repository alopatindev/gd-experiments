all:
	#g++ -o hello */*.cpp *.cpp -g -std=c++0x `pkg-config --cflags --libs clanCore-2.3 clanDisplay-2.3 clanGL1-2.3 clanApp-2.3 clanSWRender-2.3` -lpthread && gdb --eval-command=r ./hello
	g++ -o hello */*.cpp *.cpp -g -std=c++0x `pkg-config --cflags --libs clanCore-2.3 clanDisplay-2.3 clanGL1-2.3 clanApp-2.3 clanSWRender-2.3` -lpthread && gdb ./hello

clean:
	rm -f hello
