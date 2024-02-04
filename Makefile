video_service_basic: src/video_service.cpp src/test/video_service_basic.cpp
	g++ -g -Iinclude -o video_service_basic.out $^ -lSDL -lSDL_image