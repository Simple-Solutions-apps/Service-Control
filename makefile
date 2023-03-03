CC = x86_64-w64-mingw32-gcc.exe
CFlags = -Wall -O2 -D UNICODE -D _UNICODE

DirSrc = .\src
DirObj= .\obj
DirRes = .\res
DirBin = .\bin
DirLib = .\lib

APPBase = ServiceControl
APPName = $(APPBase).exe
APPPath = $(DirBin)\$(APPName)

srcMain = $(DirSrc)\main.c

srcControls = $(DirSrc)\controls.c
srcCallbacks = $(DirSrc)\callbacks.c
srcResources = $(DirRes)\main.rc

objMain = $(DirObj)\main.o
objControls = $(DirObj)\controls.o
objCallbacks = $(DirObj)\callbacks.o
objResources = $(DirObj)\resources.o

dllCommCtrls = $(DirLib)\comctl32.dll

objs = $(objMain) $(objControls) $(objCallbacks) $(objResources)

$(objMain): $(srcMain)
	$(CC) $(CFlags) -c $(srcMain) -o $(objMain)
$(objCallbacks): $(srcCallbacks)
	$(CC) $(CFlags) -c $(srcCallbacks) -o $(objCallbacks)
$(objControls): $(srcControls)
	$(CC) $(CFlags) -c $(srcControls) -o $(objControls)
$(objResources): $(srcResources)
	windres.exe --codepage=65001 $(srcResources) -o $(objResources)

build: $(objs)
	$(CC) -o $(APPPath) $(objs) $(dllCommCtrls) -s -mwindows
clean:
	del $(DirObj)\*.o $(DirBin)\*.exe
run:
	$(APPPath)
rebuild:
	make clean
	make build
commit:
	git add .
	git commit -a -m "Automated commit(s)"
	git push