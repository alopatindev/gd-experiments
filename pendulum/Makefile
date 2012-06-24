all:
	convert images/arrow.svg images/arrow.png
	g++ -o pendulum *.cpp -g -std=c++0x `pkg-config --cflags --libs clanCore-2.3 clanDisplay-2.3 clanGL1-2.3 clanApp-2.3 clanSWRender-2.3 clanSound-2.3 clanVorbis-2.3` -lpthread && gdb --eval-command=r ./pendulum

clean:
	rm -f pendulum images/arrow.png
