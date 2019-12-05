//#pragma once
//#include "main.h"
//#include <string.h>
//#pragma comment(lib,"assimp.lib")
//
//struct DEFORM_VERTEX
//{
//	aiVector3D Position;
//	aiVector3D DeformPosition;
//	aiVector3D Normal;
//	aiVector3D DeformNormal;
//	std::string BoneName[4];
//	float BoneWeight[4];	//	基本的には４
//	int BoneNum;
//};
//
//struct BONE
//{
//	aiMatrix4x4 Matrix;		// 空間上のどこにいるか
//	aiMatrix4x4 AnimationMatrix;	// 関節の回転の情報のみ
//	aiMatrix4x4 OffsetMatrix;	// このオブジェクトがボーンからどのくらいずれているか
//};
//
//class CStbTexture;
//class CModelAnimation
//{
//private:
//	CStbTexture* g_Texture;
//	CMaterial* g_Material;
//	const aiScene* g_Scene = nullptr;
//	int g_Frame;	//アニメーションのフレームカウンタ
//	const char* g_Filename = NULL;
//public:
//	void InitModelAnimation(void);
//	void DrawModelAnimation(void);
//	void UpdateModelAnimation(void);
//	void UninitModelAnimation(void);
//	void DrawModelAnimationMesh(const aiNode* node);
//	void CreateBone(aiNode* node);
//	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 Matrix);
//	void ModelViewer();
//	void LoadModelAnimation(const char* filename);
//};