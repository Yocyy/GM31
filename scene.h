#ifndef SCENE_H_
#define SCENE_H_

#include <typeinfo>
#include <vector>
#include <list>
#include "game_object.h"

enum Layer
{
	Layer_min = -1,
	Layer3D_Manager,
	Layer3D_CAMERA,
	Layer3D_MODEL,
	Layer3D_EFFECT,
	Layer2D_UI,
	Layer_max,
};


class CScene
{
protected:
	std::list<CGameObject*> m_GameObject[Layer_max];
public:
	CScene() {}
	virtual ~CScene() {}

	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (CGameObject* object : m_GameObject[Layer])

		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
		return nullptr;
	}

	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* object = new T();
		object->Init();
		m_GameObject[Layer].push_back(object);
		return object;
	}


	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects;
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	virtual void Init() = 0;

	virtual void Uninit()
	{
		for (int i = 0; i < Layer_max; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < Layer_max; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update(); 
			
			}
				m_GameObject[i].remove_if([](CGameObject* object)
				{return object->Destroy();});
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < Layer_max; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	virtual void DestroyGameObject(CGameObject* GameObject)
	{
		GameObject->SetDestroy();
	}
};

#endif // !SCENE_H_
