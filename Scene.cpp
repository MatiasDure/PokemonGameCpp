#include "Scene.h"

Scene::Scene(const string identifier, const int popForce) :
	identifier(identifier), popForce(popForce), firstRender(true) {}

//Clearing the game objects allocated in the heap
Scene::~Scene()
{
	//avoid deleting the game manager that was not allocated using the new keyword
	RemoveObjectInStack("GameManager");
	std::cout << "Destroying: " << this->identifier << endl;
	for (int i = 0; i < objectsInScene.size(); i++)
	{
		delete objectsInScene[i];
	}
}

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

void Scene::RemoveObjectInStack(const string identifierOfObj)
{
	for (int i = 0; i < this->objectsInScene.size(); i++)
	{
		if (this->objectsInScene[i]->GetIdentifier() == identifierOfObj)
		{
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

int Scene::GetPopForce(void) const
{
	return this->popForce;
}

void Scene::Update(sf::RenderWindow& window)
{
	/*for (int i = 0; i < this->objectsInScene.size(); i++)
	{
		this->objectsInScene[i]->Update(window);
	}*/
}

void Scene::RenderScene(sf::RenderWindow& window)
{
	window.clear();
	for (int i = 0; i < this->objectsInScene.size(); i++)
	{
		this->objectsInScene[i]->RenderGameObject(window);
		if(!firstRender) this->objectsInScene[i]->Update(window);
	}
	window.display();
	firstRender = false;
}

vector<GameObject*> Scene::GetObjectsInScene(void) const
{
	return this->objectsInScene;
}

string Scene::GetIdentifier(void) const
{
	return this->identifier;
}

int Scene::AmountObjectsInScene(void) const
{
	return this->objectsInScene.size();
}