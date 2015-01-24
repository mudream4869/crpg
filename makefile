CFRAME = -framework OpenGL -framework GLUT -framework Foundation -framework Python -framework OpenAL 
CFLAGS = -Wno-deprecated-declarations -std=c++11 

OBJECTS = Image.o Tile.o Map.o Hero.o Scene.o Window.o WindowMsg.o ScenePlay.o SceneStart.o Env.o Event.o SysCall.o Msg.o GlobalVariable.o Type.o Tool.o File.o WindowSelect.o SceneSave.o SceneLoad.o GameObject.o WindowGameObject.o Config.o PyLock.o

INSTANCE = Mask.o ImgCtrl.o AudioSystem.o

SCENE = SceneGameOver.o

LIBS = lodepng.o

main: $(OBJECTS) $(INSTANCE) $(SCENE) *.h
	g++ $(CFLAGS) $(CFRAME) $(OBJECTS) $(INSTANCE) $(SCENE) $(LIBS) -o test main.cpp

lodepng.o:
	g++ LoadPng/lodepng.cpp -c

%.o: %.cpp *.h
	g++ $< $(CFLAGS) -c

clear:
	rm *.o
