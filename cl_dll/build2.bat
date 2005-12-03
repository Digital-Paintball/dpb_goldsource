cp ../common/interface.cpp .
cp ../dlls/buy.cpp .
cp ../game_shared/vgui_checkbutton2.cpp .
cp ../game_shared/vgui_grid.cpp .
cp ../game_shared/vgui_helpers.cpp .
cp ../game_shared/vgui_helpers.cpp .
cp ../game_shared/vgui_listbox.cpp .
cp ../game_shared/vgui_loadtga.cpp .
cp ../game_shared/vgui_scrollbar2.cpp .
cp ../game_shared/vgui_slider2.cpp .
cp ../game_shared/voice_banmgr.cpp .
cp ../game_shared/voice_status.cpp .
cp ../game_shared/voice_vgui_tweakdlg.cpp .
cp ../pm_shared/pm_math.c .
cp ../pm_shared/pm_shared.c .
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c interface.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c buy.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_combobox.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_checkbutton2.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_grid.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_helpers.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_listbox.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_loadtga.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_scrollbar2.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_slider2.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c voice_banmgr.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c voice_status.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c voice_vgui_tweakdlg.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c pm_math.c
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c pm_shared.c
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c GameStudioModelRenderer.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c StudioModelRenderer.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c a5.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c ammo.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c ammohistory.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c angel.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c blazer.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c bush.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c cdll_int.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c cocker.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c com_weapons.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c cweapon.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c death.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c demo.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c dm4.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c emag.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c entity.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c ev_common.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c ev_hldm.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c events.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c excal.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c flag.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c flashlight.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c hl_events.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c hopper.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c hud.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c hud_msg.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c hud_redraw.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c hud_servers.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c hud_spectator.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c hud_update.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c impulse.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c in_camera.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c input.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c inputw32.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c m98.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c mag.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c matrix.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c menu.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c message.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c names.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c omen.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c orracle.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c paintball.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c parsemsg.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c phantom.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c random.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c say.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c shocker.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c sl68.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c spyder.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c status_icons.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c statusbar.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c studio_util.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c text_message.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c timer.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c timmy.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c train.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c tri.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c util.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_ConfigMenu.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_ConsolePanel.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_ControlConfigPanel.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_CustomObjects.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_MOTDWindow.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_SchemeManager.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_ScorePanel.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_ServerBrowser.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_SpectatorPanel.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_TeamFortressViewport.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_int.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c vgui_teammenu.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c view.cpp
cl /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include /c weapons.cpp
link /nologo /INCREMENTAL:no  /dll /debug /pdb:client.pdb interface.obj buy.obj vgui_combobox.obj vgui_checkbutton2.obj vgui_grid.obj vgui_helpers.obj vgui_listbox.obj vgui_loadtga.obj vgui_scrollbar2.obj vgui_slider2.obj voice_banmgr.obj voice_status.obj voice_vgui_tweakdlg.obj pm_math.obj pm_shared.obj GameStudioModelRenderer.obj StudioModelRenderer.obj a5.obj ammo.obj ammohistory.obj angel.obj blazer.obj bush.obj cdll_int.obj cocker.obj com_weapons.obj cweapon.obj death.obj demo.obj dm4.obj emag.obj entity.obj ev_common.obj ev_hldm.obj events.obj excal.obj flag.obj flashlight.obj hl_events.obj hopper.obj hud.obj hud_msg.obj hud_redraw.obj hud_servers.obj hud_spectator.obj hud_update.obj impulse.obj in_camera.obj input.obj inputw32.obj m98.obj mag.obj matrix.obj menu.obj message.obj names.obj omen.obj orracle.obj paintball.obj parsemsg.obj phantom.obj random.obj say.obj shocker.obj sl68.obj spyder.obj status_icons.obj statusbar.obj studio_util.obj text_message.obj timer.obj timmy.obj train.obj tri.obj util.obj vgui_ConfigMenu.obj vgui_ConsolePanel.obj vgui_ControlConfigPanel.obj vgui_CustomObjects.obj vgui_MOTDWindow.obj vgui_SchemeManager.obj vgui_ScorePanel.obj vgui_ServerBrowser.obj vgui_SpectatorPanel.obj vgui_TeamFortressViewport.obj vgui_int.obj vgui_teammenu.obj view.obj weapons.obj user32.lib winmm.lib wsock32.lib c:/vgui.lib
