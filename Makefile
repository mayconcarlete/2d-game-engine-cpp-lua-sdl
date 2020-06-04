build:
	g++ -w -std=c++14 -Wfatal-errors \
	./src/*.cpp \
	./src/Entity/*.cpp \
	./src/EntityManager/*.cpp \
	./src/AssetManager/*.cpp \
	./src/TextureManager/*.cpp \
	-o game \
	-I"./lib/lua" \
	-L"./lib/lua" \
	-llua5.3 \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

clean:
	rm ./game;

run:
	./game;