all:
	g++ source/light.cpp source/FastTrackball.cpp source/controller.cpp source/view.cpp source/main.cpp source/model.cpp source/object.cpp source/face.cpp source/vertex.cpp -w -lglut -lGL -lGLU -lSOIL -o bin/exec 

run:
	g++ source/light.cpp source/FastTrackball.cpp source/controller.cpp source/view.cpp source/object.cpp source/face.cpp source/vertex.cpp source/main.cpp source/model.cpp -w -lglut -lGL -lGLU -lSOIL -o bin/exec 
	bin/./exec ${ARGS}
