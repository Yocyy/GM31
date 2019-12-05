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
//	float BoneWeight[4];	//	��{�I�ɂ͂S
//	int BoneNum;
//};
//
//struct BONE
//{
//	aiMatrix4x4 Matrix;		// ��ԏ�̂ǂ��ɂ��邩
//	aiMatrix4x4 AnimationMatrix;	// �֐߂̉�]�̏��̂�
//	aiMatrix4x4 OffsetMatrix;	// ���̃I�u�W�F�N�g���{�[������ǂ̂��炢����Ă��邩
//};
//
//class CStbTexture;
//class CModelAnimation
//{
//private:
//	CStbTexture* g_Texture;
//	CMaterial* g_Material;
//	const aiScene* g_Scene = nullptr;
//	int g_Frame;	//�A�j���[�V�����̃t���[���J�E���^
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