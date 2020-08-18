#include "vertex.h"

#pragma once

class Face {	
	public:
		vector<Vertex> vertices;
		float normal[3];
		Face();
		~Face();
};