# Digital Paintball: Gold

This is the source code for the Half-life 1 modification Digital Paintball.

The project has been updated with a Visual Studio 2019 project. All you should need to do is clone this repository and build the solution. The DLL's will be available in `build/`. 

To debug, set the configuration to "Debug" and build the solution. Start the mod. Goto the "Debug" menu and choose "Attach to Process...". Look through the list of processes and select `hl.exe`. The breakpoints will load after a game has been started. You can also attach the session after a game has been started.

For the lazy, there is a batch script provided that copies the DLL's to the game directories. To use it, you need to set two environment variables. 

* `DPB_CLIENT_OUTPUT_DIR`: The directory where `client.dll` goes, e.g. `dpb\cl_dlls\client.dll`.
* `DPB_SERVER_OUTPUT_DIR`: The directory where `pb.dll` goes, e.g. `dpb\dlls\pb.dll`.

```
D:\dpbgoldsrc> copy_dlls.bat debug
Mode:        debug
Client dir:  D:\Steam\steamapps\common\Half-Life\dpb\cl_dlls
Server dir:  D:\Steam\steamapps\common\Half-Life\dpb\dlls
        1 file(s) copied.
	1 file(s) copied.
```

