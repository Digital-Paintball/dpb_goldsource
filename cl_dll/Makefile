OFS = interface.obj buy.obj vgui_combobox.obj vgui_checkbutton2.obj vgui_grid.obj vgui_helpers.obj vgui_listbox.obj vgui_loadtga.obj vgui_scrollbar2.obj vgui_slider2.obj voice_banmgr.obj voice_status.obj voice_vgui_tweakdlg.obj pm_math.obj pm_shared.obj GameStudioModelRenderer.obj StudioModelRenderer.obj a5.obj ammo.obj ammohistory.obj angel.obj blazer.obj bush.obj cdll_int.obj cocker.obj com_weapons.obj cweapon.obj death.obj demo.obj dm4.obj emag.obj entity.obj ev_common.obj ev_hldm.obj events.obj excal.obj flag.obj flashlight.obj hl_events.obj hopper.obj hud.obj hud_msg.obj hud_redraw.obj hud_servers.obj hud_spectator.obj hud_update.obj impulse.obj in_camera.obj input.obj inputw32.obj m98.obj mag.obj matrix.obj menu.obj message.obj names.obj omen.obj orracle.obj paintball.obj parsemsg.obj phantom.obj random.obj say.obj shocker.obj sl68.obj spyder.obj status_icons.obj statusbar.obj studio_util.obj text_message.obj timer.obj timmy.obj train.obj tri.obj util.obj vgui_ConfigMenu.obj vgui_ConsolePanel.obj vgui_ControlConfigPanel.obj vgui_CustomObjects.obj vgui_MOTDWindow.obj vgui_SchemeManager.obj vgui_ScorePanel.obj vgui_ServerBrowser.obj vgui_SpectatorPanel.obj vgui_TeamFortressViewport.obj vgui_int.obj vgui_teammenu.obj view.obj weapons.obj
COPIED = interface.cpp buy.cpp vgui_checkbutton2.cpp vgui_grid.cpp vgui_helpers.cpp vgui_listbox.cpp vgui_loadtga.cpp vgui_scrollbar2.cpp vgui_slider2.cpp voice_banmgr.cpp voice_status.cpp voice_vgui_tweakdlg.cpp pm_math.c pm_shared.c
#CFLAGS = /nologo /Zi /ZI  /MLd /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include
CFLAGS = /nologo /O2 /ML /G5 /EHsc /W3 /D WIN32 /D _WINDOWS /D CLIENT_WEAPONS /D CLIENT_DLL -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared -I../utils/vgui/include -I/cygdrive/c/vs/include -I/cygdrive/c/vs/PlatformSDK/include
LFLAGS = /nologo /INCREMENTAL:no /subsystem:windows /out:client.dll /dll /debug /pdb:"client.pdb"
LIBS = user32.lib winmm.lib wsock32.lib c:/vgui.lib
client.dll: ${COPIED} ${OFS}
	link ${LFLAGS} ${OFS} ${LIBS}
	echo link ${LFLAGS} ${OFS} ${LIBS} >> build.bat
interface.cpp: ../common/interface.cpp
	cp $< .
	echo cp $< . > build.bat
buy.cpp: ../dlls/buy.cpp
	cp $< .
	echo cp $< . >> build.bat
vgui_checkbutton2.cpp: ../game_shared/vgui_checkbutton2.cpp
	cp $< .
	echo cp $< . >> build.bat
vgui_grid.cpp: ../game_shared/vgui_grid.cpp
	cp $< .
	echo cp $< . >> build.bat
vgui_helpers.cpp: ../game_shared/vgui_helpers.cpp
	cp $< .
	echo cp $< . >> build.bat
	echo cp $< . >> build.bat
vgui_listbox.cpp: ../game_shared/vgui_listbox.cpp
	cp $< .
	echo cp $< . >> build.bat
vgui_loadtga.cpp: ../game_shared/vgui_loadtga.cpp
	cp $< .
	echo cp $< . >> build.bat
vgui_scrollbar2.cpp: ../game_shared/vgui_scrollbar2.cpp
	cp $< .
	echo cp $< . >> build.bat
vgui_slider2.cpp: ../game_shared/vgui_slider2.cpp
	cp $< .
	echo cp $< . >> build.bat
voice_banmgr.cpp: ../game_shared/voice_banmgr.cpp
	cp $< .
	echo cp $< . >> build.bat
voice_status.cpp: ../game_shared/voice_status.cpp
	cp $< .
	echo cp $< . >> build.bat
voice_vgui_tweakdlg.cpp: ../game_shared/voice_vgui_tweakdlg.cpp
	cp $< .
	echo cp $< . >> build.bat
pm_math.c: ../pm_shared/pm_math.c
	cp $< .
	echo cp $< . >> build.bat
pm_shared.c: ../pm_shared/pm_shared.c
	cp $< .
	echo cp $< . >> build.bat
%.obj: %.cpp
	cl ${CFLAGS} /c $<
	echo cl ${CFLAGS} /c $< >> build.bat
%.obj: %.c
	cl ${CFLAGS} /c $<
	echo cl ${CFLAGS} /c $< >> build.bat
clean:
	rm ${OFS} client.* ${COPIED}
	echo rm ${OFS} client.* ${COPIED} > clean.bat