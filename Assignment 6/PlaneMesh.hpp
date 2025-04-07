
class PlaneMesh {
	
	std::vector<float> verts;
	std::vector<float> normals;
	std::vector<int> indices;

	float min, max;
	glm::vec4 modelColor;
	int numVerts, numIndices;


	void planeMeshQuads(float min, float max, float stepsize) {

		// The following coordinate system works as if (min, 0, min) is the origin
		// And then builds up the mesh from that origin down (in z)
		// and then to the right (in x).
		// So, one "row" of the mesh's vertices have a fixed x and increasing z

		//manually create a first column of vertices
		float x = min;
		float y = 0;
		for (float z = min; z <= max; z += stepsize) {
			verts.push_back(x);
			verts.push_back(y);
			verts.push_back(z);
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);
		}

		for (float x = min+stepsize; x <= max; x += stepsize) {
			for (float z = min; z <= max; z += stepsize) {
				verts.push_back(x);
				verts.push_back(y);
				verts.push_back(z);
				normals.push_back(0);
				normals.push_back(1);
				normals.push_back(0);
			}
		}

		int nCols = (max-min)/stepsize + 1;
		int i = 0, j = 0;
		for (float x = min; x < max; x += stepsize) {
			j = 0;
			for (float z = min; z < max; z += stepsize) {
				indices.push_back(i*nCols + j);
				indices.push_back(i*nCols + j + 1);
				indices.push_back((i+1)*nCols + j + 1);
				indices.push_back((i+1)*nCols + j);
				++j;
			}
			++i;
		}
	}
GLuint vaoID, vboID, nboID, eboID;

public:

	PlaneMesh(float min, float max, float stepsize) {
		this->min = min;
		this->max = max;
		modelColor = glm::vec4(0, 1.0f, 1.0f, 1.0f);

		planeMeshQuads(min, max, stepsize);
		numVerts = verts.size()/3;
		numIndices = indices.size();
		
		//gen and fill buffers
		glGenVertexArrays(1, &vaoID);
		glGenBuffers(1, &vboID);
		glGenBuffers(1, &nboID);
		glGenBuffers(1, &eboID);

		glBindVertexArray(vaoID);

		//vertex attribute pointers
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), &verts[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//shaders and uniforms
		// Normals
		glBindBuffer(GL_ARRAY_BUFFER, nboID);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	void draw() {
		glBindVertexArray(vaoID);
		glDrawElements(GL_PATCHES, numIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

};
