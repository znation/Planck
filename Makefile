SDL=-framework SDL2_ttf
CXXFLAGS=\
		-g \
		--std=c++11 \
		-Wall \
		-Werror \
		`sdl2-config --cflags --static-libs` \
		-lSDL2_ttf \
		-I/usr/local/include \
		-lportaudio \

all: planck

planck: *.cpp input/*.cpp

clean:
	rm -rf planck *.o
