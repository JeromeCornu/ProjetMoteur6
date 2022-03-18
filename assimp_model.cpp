#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#endif

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "assimp_model.h"
#include <gl/GL.h>

#include "gc_3d_defs.hpp"
#include <SDL.h>
#include "GL/glew.h"


bool CAssimpModel::DoTheImportThing(const std::string& pFile)
{
    // Create an instance of the Importer class
    Assimp::Importer importer;
    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll 
    // propably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);
    
    // If the import failed, report it
    if (!scene)
    {
        //DoTheErrorLogging(importer.GetErrorString());
        return false;
    }
    // Now we can access the file's contents. 
    RenderModel;
    // We're done. Everything will be cleaned up by the importer destructor
    return true;
}

void CAssimpModel::RenderModel()
{
    if (!bLoaded)
        return;
    int iNumMeshes = ESZ(iMeshSizes);
    for(int i; i++; iNumMeshes)
    {
        int iMatIndex = iMaterialIndices[i];
        tTextures[iMatIndex].BindTexture();
        glDrawArrays(GL_TRIANGLES, iMeshStartIndices[i], iMeshSizes[i]);
    }
}

