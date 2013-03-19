#include "Model.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Model::Model(std::string filename, bool invert) {
	std::vector<Vertex> vertex_data;
	std::vector<unsigned int> indices_data;

	aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);
	unsigned int load_flags = aiProcessPreset_TargetRealtime_Quality;;

	//if (invert) load_flags |= aiProcess_ConvertToLeftHanded;

	scene = aiImportFile(filename.c_str(), load_flags);
	if (!scene) {
		std::string log = "Unable to load mesh from ";
		log.append(filename);
		throw std::runtime_error(log);
	}

	//Load the model recursively into data
	min_dim = glm::vec3(std::numeric_limits<float>::max());
	max_dim = -glm::vec3(std::numeric_limits<float>::max());

	//std::cout << min_dim.x << ", " << min_dim.y << ", " << min_dim.z << " - "  << max_dim.x << ", " << max_dim.y << ", " << max_dim.z << std::endl;
	loadRecursive(root, invert, vertex_data, indices_data, max_dim, min_dim, scene, scene->mRootNode, trafo);
	

	//Translate to center
	glm::vec3 translation = (max_dim - min_dim) / glm::vec3(2.0f) + min_dim;
	glm::vec3 scale_helper = glm::vec3(2.0f)/(max_dim - min_dim);
	glm::vec3 scale = glm::vec3(std::min(scale_helper.x, std::min(scale_helper.y, scale_helper.z)));
	if (invert) scale = -scale;
	
	root.transform = glm::mat4(1.0);
	root.transform = glm::scale(root.transform, scale);
	root.transform = glm::translate(root.transform, -translation);

	//Create the VBOs from the data.
	if (fmod(static_cast<float>(indices_data.size()), 3.0f) < 0.000001f) 
	{
		InterleavedVBO.reset(new GLUtils::BO<GL_ARRAY_BUFFER>(vertex_data.data(), vertex_data.size()*sizeof(Vertex)));
		indices.reset(new GLUtils::BO<GL_ELEMENT_ARRAY_BUFFER>(indices_data.data(), indices_data.size() * sizeof(unsigned int)));

		stride = sizeof(Vertex);
		verticeOffset = NULL;
		normalOffset = (GLvoid*)(3*sizeof(float));
		//texCoordOffset = (GLvoid*)(6*sizeof(float));
	}
	else
		THROW_EXCEPTION("The number of vertices in the mesh is wrong");
}

Model::~Model() {

}

void Model::loadRecursive(bool invert,
			std::vector<float>& vertex_data, std::vector<float>& normal_data, 
			std::vector<float>& color_data, 
			const aiScene* scene, const aiNode* node, aiMatrix4x4 modelview_matrix) {
	//update transform matrix. notice that we also transpose it
	aiMultiplyMatrix4(&modelview_matrix, &node->mTransformation);
	aiMatrix4x4 normal_matrix = modelview_matrix.Inverse().Transpose();

	// draw all meshes assigned to this node
	for (unsigned int n=0; n < node->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[node->mMeshes[n]];

		unsigned int count = mesh->mNumFaces*3;

		//Allocate data
		vertex_data.reserve(vertex_data.size() + count*3);
		if (mesh->HasNormals()) 
			normal_data.reserve(normal_data.size() + count*3);
		if (mesh->mColors[0] != NULL) 
 			color_data.reserve(color_data.size() + count*4);

		//Add the vertices from file
		for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;
			
			if(face->mNumIndices != 3) {
				std::cout << "Vertex count for face was " << face->mNumIndices << ", expected 3. Skipping face" << std::endl;
				continue;
				//throw std::runtime_error("Only triangle meshes are supported");
			}

			for(unsigned int i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				aiVector3D tmp = mesh->mVertices[index];
				aiTransformVecByMatrix4(&tmp, &modelview_matrix);

				vertex_data.push_back(tmp.x);
				vertex_data.push_back(tmp.y);
				vertex_data.push_back(tmp.z);
				
				if (mesh->HasNormals()) {
					tmp = mesh->mNormals[index];
					aiTransformVecByMatrix4(&tmp, &normal_matrix);

					if (!invert) {
						normal_data.push_back(tmp.x);
						normal_data.push_back(tmp.y);
						normal_data.push_back(tmp.z);
					}
					else {
						normal_data.push_back(-tmp.x);
						normal_data.push_back(-tmp.y);
						normal_data.push_back(-tmp.z);
					}
				}
				
				if (mesh->mColors[0] != NULL) {
					color_data.push_back(mesh->mColors[0][index].r);
					color_data.push_back(mesh->mColors[0][index].g);
					color_data.push_back(mesh->mColors[0][index].b);
					color_data.push_back(mesh->mColors[0][index].a);
				}
			}
		}
	}

	// load all children
	for (unsigned int n = 0; n < node->mNumChildren; ++n)
		loadRecursive(invert, vertex_data, normal_data, color_data, scene, node->mChildren[n], modelview_matrix);
}

void Model::loadRecursive( MeshPart& part, bool invert, std::vector<Vertex>& vertex_data, 
					       std::vector<unsigned int>& indices, glm::vec3& max_dim, glm::vec3& min_dim, 
						   const aiScene* scene, const aiNode* node, aiMatrix4x4 modelview_matrix )
{
	//update transform matrix. notice that we also transpose it
	aiMatrix4x4 m = node->mTransformation;
	for (int j=0; j<4; ++j)
		for (int i=0; i<4; ++i)
			part.transform[j][i] = m[i][j];


	// draw all meshes assigned to this node
	for (unsigned int n=0; n < node->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[node->mMeshes[n]];

		part.first = indices.size();
		part.count = mesh->mNumFaces*3;

		unsigned int indexOffset = vertex_data.size();
		vertex_data.reserve(vertex_data.size() + part.count*3);
		indices.reserve(indices.size() + mesh->mNumVertices*3);

		bool has_normals = mesh->HasNormals();
		//part.texCoords0 = mesh->HasTextureCoords(0);

		for(unsigned int v = 0; v < mesh->mNumVertices; v++){
			Vertex new_vertex;
			new_vertex.vertex = glm::vec3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);

			checkDimensions(new_vertex.vertex, max_dim, min_dim);

			if(has_normals)
				new_vertex.normal = glm::vec3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);

			/*if(part.texCoords0)
			new_vertex.texCoord0 = glm::vec2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);
			else
			new_vertex.texCoord0 = glm::vec2(0.0f, 0.0f);*/

			vertex_data.push_back(new_vertex);
		}
		
		//Storing the indices of this meshPart. Applying index offset
		//to each index, matching the number of vertices already stored
		//in the vector from other meshparts
		for(unsigned int t = 0; t < mesh->mNumFaces; ++t)
		{
			const struct aiFace* face = &mesh->mFaces[t];
			if(face->mNumIndices != 3)
				THROW_EXCEPTION("Only triangle meshes are supported");
			for(unsigned int i = 0; i < face->mNumIndices; i++) {
				indices.push_back(face->mIndices[i]+indexOffset);
			}
		}
	}

	// load all children
	for (unsigned int n = 0; n < node->mNumChildren; ++n)
	{
		loadRecursive(part, invert, vertex_data, indices, max_dim, min_dim, 
					scene, node->mChildren[n], modelview_matrix);
	}
}

void Model::checkDimensions( glm::vec3 newVertex, glm::vec3& max_dim, glm::vec3& min_dim )
{
	if(newVertex.x < min_dim.x)
		min_dim.x = newVertex.x;
	if(newVertex.y < min_dim.y)
		min_dim.y = newVertex.y;
	if(newVertex.z < min_dim.z)
		min_dim.z = newVertex.z;

	if(newVertex.x > max_dim.x)
		max_dim.x = newVertex.x;
	if(newVertex.y > max_dim.y)
		max_dim.y = newVertex.y;
	if(newVertex.z > max_dim.z)
		max_dim.z = newVertex.z;
}
