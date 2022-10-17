#include "Scene.h"

Scene::Scene(const string indentifier) :
	identifier(identifier) {}

void Scene::AddObject(GameObject* objToAdd)
{
	this->objectsInScene.push_back(objToAdd);
}

void Scene::RemoveObject(const string identifierOfObj)
{
	for (int i = 0; i < this->objectsInScene.size(); i++)
	{
		if (this->objectsInScene[i]->GetIdentifier() == identifierOfObj)
		{
			//freeing memory space
			delete this->objectsInScene[i];
			this->objectsInScene.erase(objectsInScene.begin() + i);
			break;
		}
	}
}

void Scene::HandleEvent(sf::Event& event, sf::RenderWindow& window)
{
	for (int i = 0; i < objectsInScene.size(); i++)
	{
		objectsInScene[i]->HandleEvent(event, window);
	}
}

//void Scene::Update(sf::RenderWindow& window)
//{
//	for (int i = 0; i < this->objectsInScene.size(); i++)
//	{
//		this->objectsInScene[i]->Update(window);
//	}
//}

void Scene::RenderScene(sf::RenderWindow& window)
{
	window.clear();
	for (int i = 0; i < this->objectsInScene.size(); i++)
	{
		this->objectsInScene[i]->RenderGameObject(window);
		this->objectsInScene[i]->Update(window);
	}
	window.display();
}

vector<GameObject*> Scene::GetObjectsInScene() const
{
	return objectsInScene;
}

string Scene::GetIdentifier() const
{
	return this->identifier;
}

int Scene::AmountObjectsInScene() const
{
	return this->objectsInScene.size();
}