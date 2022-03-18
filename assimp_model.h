#include <string>


class CAssimpModel
{
public:
	bool DoTheImportThing(const std::string& pFile);
	void RenderModel();

private:
	bool bLoaded;
	static vector<CTexture> tTextures;
	vector<int> iMeshStartIndices;
	vector<int> iMeshSizes;
	vector<int> iMaterialIndices;
};