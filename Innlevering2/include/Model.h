#ifndef _MODEL_H__
#define _MODEL_H__

#include <memory>
#include <string>
#include <vector>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils/BO.hpp"
#include "GameException.h"

struct MeshPart 
{
	MeshPart() 
	{
		transform = glm::mat4(1.0f);
		first = 0;
		count = 0;
		texCoords0 = false;
	}

	glm::mat4 transform;

	unsigned int first;	//<this meshParts initial index offset in the VBO
	unsigned int count;	//<the index length of this meshPart

	std::vector<std::string> diffuseTextures;
	std::vector<std::string> normalTextures;
	std::vector<std::string> specularTextures;

	bool texCoords0;//<true if the meshPart has one texture coord collection

	std::vector<MeshPart> children;
};

struct Vertex
{
	glm::vec3 vertex;
	glm::vec3 normal;
	glm::vec2 texCoord0;
};


class Model {
public:
	Model(std::string filename, bool invert=0);
	~Model();

	inline unsigned int getNVertices() {return n_vertices;}
	inline glm::mat4 getTransform() {return transform;}

	inline std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > getVertices() {return vertices;}
	inline std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > getNormals() {return normals;}
	inline std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > getColors() {return colors;}

	inline std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > getInterleavedVBO(){return InterleavedVBO;}
	inline std::shared_ptr<GLUtils::BO<GL_ELEMENT_ARRAY_BUFFER> > getIndices(){return indices;}

	//Returns the stride, use for interleaved VBOs
	inline GLint getStride(){return stride;}

	//the offsets returns the offset used by interleaved VBOs as a GLVoid*
	inline GLvoid* getVerticeOffset() {return verticeOffset;}
	inline GLvoid* getNormalOffset() {return normalOffset;}
	inline GLvoid* getTexCoordOffset() {return texCoordOffset;}

private:
	static void loadRecursive(bool invert,
			std::vector<float>& vertex_data, std::vector<float>& normal_data, 
			std::vector<float>& color_data,
			const aiScene* scene, const aiNode* node, aiMatrix4x4 modelview_matrix);
			
	static void loadRecursive(MeshPart& part, bool invert,
		std::vector<Vertex>& vertex_data,
		std::vector<unsigned int>& indices,
		glm::vec3& max_dim, glm::vec3& min_dim,
		const aiScene* scene, const aiNode* node, aiMatrix4x4 modelview_matrix);

	/*
	* Helper function to see if x, y or z are bigger or smaller
	* than the x, y and z stored in max_dim and min_dim. If any value
	* matches the criteria (smaller than current value in min_dim, or
	* bigger than current value in max_dim), the value in the reference
	* vector is replaced
	*/
	static void checkDimensions(glm::vec3 newVertex, glm::vec3& max_dim, glm::vec3& min_dim);
	

	const aiScene* scene;
	MeshPart root;

	std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > normals;
	std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > vertices;
	std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > colors;

	std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > InterleavedVBO;
	std::shared_ptr<GLUtils::BO<GL_ELEMENT_ARRAY_BUFFER> > indices;

	GLint stride;			//< Stride value for the interleavedVBO
	GLvoid* verticeOffset;	//< Offset value for the vertices (should be NULL)
	GLvoid* normalOffset;	//< Offset value for the normals (should be 3*sizeof(float))
	GLvoid* texCoordOffset;	//< Offset value for the textureCoords, if there are any(should be 6*sizeof(float))


	glm::vec3 min_dim;
	glm::vec3 max_dim;
	glm::mat4 transform;

	unsigned int n_vertices;
};

#endif