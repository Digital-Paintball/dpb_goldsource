OFS =  a5.o angel.o animating.o animation.o blazer.o bmodels.o bush.o buttons.o buy.o cbase.o client.o cocker.o combat.o dm4.o doors.o effects.o emag.o excal.o explode.o func_break.o func_tank.o game.o globals.o h_cycler.o h_export.o impulse.o lights.o m98.o mag.o matrix.o mortar.o mpstubb.o object.o omen.o orracle.o paintball.o pathcorner.o pbgun.o phantom.o plane.o plats.o player.o random.o rules.o shocker.o sl68.o sound.o soundent.o spectator.o spyder.o studio_util.o subs.o timmy.o triggers.o util.o world.o pm_shared.o pm_math.o voice_gamemgr.o
COPIED = pm_shared.c pm_math.c voice_gamemgr.cpp
CFLAGS = -I../dlls -I../pm_shared -I../engine -I../common -I../game_shared
all:
	@echo "need a target: pb_i686.so pb.dll"
pb.dll: ${OFS}
	${CPP} -mno-cygwin  -shared  -Wl,--kill-at -o pb.dll ${OFS}
	strip -s pb.dll
pb_i686.so: ${OFS} pb.map
	${CPP} -shared -Wl,--version-script=pb.map -o pb_i686.so -static-libgcc -L. ${OFS}
	strip -R .sym pb_i686.so
pb.map:
	grep LINK_ENTITY_TO_CLASS *.cpp | perl genmap.pl > pb.map
pm_shared.c: ../pm_shared/pm_shared.c
	cp $< .
pm_math.c: ../pm_shared/pm_math.c
	cp $< .
voice_gamemgr.cpp: ../game_shared/voice_gamemgr.cpp
	cp $< .
.cpp.o:
	${CPP} ${OSFLAGS} ${CFLAGS} -c $<
.c.o:
	${CC} ${OSFLAGS} ${CFLAGS} -c $<
clean:
	rm ${OFS} *.obj pb.map pb.dll pb_i686.so ${COPIED}
