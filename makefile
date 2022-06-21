CC = x86_64-w64-mingw32-gcc.exe
CFlags = -Wall -O2 -Werror

DirSrc = .\src
DirObj= .\obj
DirRes = .\res
DirBin = .\bin
DirLib = .\lib

APP = $(DirBin)\ServiceControl.exe

srcMain = $(DirSrc)\main.c
srcMsgBoxes = $(DirSrc)\MsgBoxes.c
srcControls = $(DirSrc)\controls.c
srcCallbacks = $(DirSrc)\callbacks.c
srcResources = $(DirRes)\main.rc

objMain = $(DirObj)\main.o
objMsgBoxes = $(DirObj)\MsgBoxes.o
objControls = $(DirObj)\controls.o
objCallbacks = $(DirObj)\callbacks.o
objResources = $(DirObj)\resources.o

dllCommCtrls = $(DirLib)\comctl32.dll

objs = $(objMain) $(objMsgBoxes) $(objControls) $(objCallbacks) $(objResources)

$(objMain): $(srcMain)
	$(CC) $(CFlags) -c $(srcMain) -o $(objMain)
$(objCallbacks): $(srcCallbacks)
	$(CC) $(CFlags) -c $(srcCallbacks) -o $(objCallbacks)
$(objControls): $(srcControls)
	$(CC) $(CFlags) -c $(srcControls) -o $(objControls)
$(objMsgBoxes): $(srcMsgBoxes)
	$(CC) $(CFlags) -c $(srcMsgBoxes) -o $(objMsgBoxes)
$(objResources): $(srcResources)
	windres.exe $(srcResources) -o $(objResources)

build: $(objs)
	$(CC) -o $(APP) $(objs) $(dllCommCtrls) -s -mwindows
clean:
	del $(DirObj)\*.o $(DirBin)\*.exe
run:
	$(APP)
rebuild:
	make clean
	make build
commit:
	copy /Y C:\Bak\Projects\VSCodeWorkspace\.vscode\tasks.json .\VSCode\tasks.json
	copy /Y %AppData%\code\user\keybindings.json .\VSCode\keybindings.json
	git add .
	git commit -a -m "Automated commit(s)"
	git push