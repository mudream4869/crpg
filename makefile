CFRAME = -framework OpenGL -framework GLUT -framework Foundation -framework Python -framework OpenAL 
CFLAGS = -Wno-deprecated-declarations -std=c++11 

OBJECTS = Image.o Tile.o Map.o Hero.o Scene.o Window.o WindowMsg.o ScenePlay.o SceneStart.o Env.o Event.o SysCall.o Msg.o GlobalVariable.o Type.o Tool.o File.o WindowSelect.o SceneSave.o SceneLoad.o GameObject.o WindowGameObject.o AudioSystem.o Config.o

LIBS = lodepng.o

main: $(OBJECTS) *.h
	g++ $(CFLAGS) $(CFRAME) $(OBJECTS) $(LIBS) -o test main.cpp

lodepng.o:
	g++ LoadPng/lodepng.cpp -c

%.o: %.cpp *.h
	g++ $< $(CFLAGS) -c

clear:
	rm *.o
