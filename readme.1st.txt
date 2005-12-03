dpb 2.2a source code

compiling
	dpb was originally set up to compile with gnumake under cygwin. I modified
	the make files to create batch files (build.bat) for both the client and the
	server. If you just want to build the dlls without any hassle, just use the batch files.
	If you want to build them the way that we build them, grab cygwin and make sure
	the the gnu make utility is installed. through the Visual Studio .NET 2003 Command Prompt,
	run cygwin, and then cd to the code's directory (cl_dlls or dlls) and type make. for the server,
	make -f Makefile.win32 is required. To use the batch files, run build.bat through the
	Visual Studio .NET 2003 Command Prompt.

current issues (in order of severity):

	hlds crash on changelevel in internet game with players connected
		steps to reproduce:
			launch hlds
			have people join game
			changelevel (keep changing the level with the changelevel command
				until it segfaults)

	prone/stamina system input is broken
		steps to reproduce:
			join game
			hit prone twice
			prone will prone, then wait for stamina to go full to unprone.
				the expected behavior is to ignore the second keypress, not store it.
				also, if you are prone at the end of a round or when shot, you will start
				the next round with prone queued.
			
	view models glitch around screen in internet games
		steps to reproduce:
			launch game
			start server or connect to server
			when another player joins your server, or if you have connected
				to another server,
			event occurs 'randomly' - it seems like memory is being overwritten
				somewhere. view models will move around the screen and sometimes
				disappear.

feature requests:

	have the ability to save the buy menu configuration to a bind, or something.
	implement trigger bouncing (see input.cpp on the client for more info)
