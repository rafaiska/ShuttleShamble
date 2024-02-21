LANG = en_US.UTF-8
CFLAGS = -Iinclude -Wfatal-errors -std=c++17

video_service_basic: src/video_service.cpp src/test/video_service_basic.cpp
	g++ -g -o video_service_basic.out $^ -lSDL -lSDL_image ${CFLAGS}

obj/%.o: src/%.cpp
	g++ ${CFLAGS} -c -g -o $@ $^

obj/test/%.o: src/test/%.cpp
	g++ ${CFLAGS} -c -g -o $@ $^

all_tests.out: obj/cp_collision.o obj/game_object.o obj/main_loop.o obj/manager.o obj/video_service.o obj/test/collision_test.o src/test/gtest_main.cpp
	g++ ${CFLAGS} -g -o $@ $^ -lgtest -lpthread -lSDL -lSDL_image