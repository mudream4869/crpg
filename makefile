CFRAME = -framework OpenGL -framework GLUT -framework Foundation -framework Python -framework OpenAL 
CFLAGS = -Wno-deprecated-declarations -std=c++11 

OBJECTS = Image.o Tile.o Map.o Hero.o Event.o Type.o Tool.o File.o Config.o

INSTANCE = Mask.o ImgCtrl.o AudioSystem.o GlobalVariable.o Msg.o GameObject.o PyLock.o SysCall.o Env.o

SCENE = Scene.o ScenePlay.o SceneGameOver.o SceneStart.o SceneSave.o SceneLoad.o

WINDOW = Window.o WindowBlockType.o WindowMsg.o WindowSelect.o WindowGameObject.o WindowInputNumber.o

LIBS = lodepng.o

main: $(OBJECTS) $(INSTANCE) $(SCENE) $(WINDOW) *.h
	g++ $(CFLAGS) $(CFRAME) $(OBJECTS) $(INSTANCE) $(SCENE) $(WINDOW) $(LIBS) -o test main.cpp

lodepng.o:
	g++ LoadPng/lodepng.cpp -c

%.o: %.cpp *.h
	g++ $< $(CFLAGS) -c

clear:
	rm *.o
