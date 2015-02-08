os_switch: os_switch.cpp
	$(CXX) os_switch.cpp -o os_switch

OS = $(shell ./os_switch)

CFLAGS = $(CFLAG)
CFLAGS += -Wno-deprecated-declarations -std=c++11

ifeq ($(OS), apple)
CFRAME = -framework OpenGL -framework GLUT -framework Foundation -framework Python -framework OpenAL 
endif

ifeq ($(OS), $(filter $(OS), freebsd linux))
CFLAGS += -pthread
CFRAME = $(shell pkg-config --libs gl glu python-2.7 openal) -lglut
endif

ifeq ($(OS), win32)
CFRAME = -lpython2.7 
CFRAME += -llibOpenAL32 
CFRAME += -lopengl32 -lglu32 -lglut
#CFLAGS += -D_STDCALL_SUPPORTED -D_M_IX86
endif

OBJECTS = Image.o Tile.o Map.o Hero.o Event.o Type.o Tool.o File.o Config.o Script.o Object.o

COMPONENT = MoverComponent.o GraphicComponent.o

INSTANCE = Mask.o ImgCtrl.o AudioSystem.o GlobalVariable.o GameObject.o PyLock.o SysCall.o InputCtrl.o

SCENE = Scene.o ScenePlay.o SceneGameOver.o SceneStart.o SceneSave.o SceneLoad.o

WINDOW = Window.o WindowBlockType.o WindowMsg.o WindowSelect.o WindowGameObject.o WindowInputNumber.o WindowMsgSelect.o

LIBS = lodepng.o

main: $(OBJECTS) $(INSTANCE) $(SCENE) $(WINDOW) $(COMPONENT) *.h $(LIBS)
	$(CXX) main.cpp $(CFLAGS) $(OBJECTS) $(INSTANCE) $(SCENE) $(WINDOW) $(COMPONENT) $(LIBS)  $(CFRAME) -o test

lodepng.o:
	$(CXX) loadpng/lodepng.cpp -c $(CFLAGS)

%.o: %.cpp *.h
	$(CXX) $< $(CFLAGS) -c

clear:
	rm *.o
