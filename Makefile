LANG = en_US.UTF-8
CFLAGS = -Iinclude -Wfatal-errors -std=c++17

video_service_basic: obj/tile.o obj/utils.o obj/image.o obj/video_service_sdl1.o obj/test/video_service_basic.o
	g++ -g -o video_service_basic.out $^ -lSDL -lSDL_image ${CFLAGS}

obj/%.o: src/%.cpp
	g++ ${CFLAGS} -c -g -o $@ $^

obj/test/%.o: src/test/%.cpp
	g++ ${CFLAGS} -c -g -o $@ $^

all_tests.out: obj/cp_collision.o obj/sprite.o obj/tile.o obj/image.o obj/cp_renderer.o obj/camera.o obj/game_object.o obj/main_loop.o obj/file.o obj/manager.o obj/asset_manager.o obj/data_tree.o obj/video_service_mock.o obj/file_service.o obj/utils.o obj/test/collision_test.o obj/test/utils_test.o obj/test/renderer_test.o obj/test/file_test.o obj/test/data_tree_test.o obj/test/assets_file_test.o obj/test/tilemap_test.o obj/test/test_utils.o src/test/gtest_main.cpp
	g++ ${CFLAGS} -g -o $@ $^ -lgtest -lpthread -lSDL -lSDL_image -lxxhash -ltinyxml2 -lz

clear:
	rm obj/*.o
	rm obj/test/*.o