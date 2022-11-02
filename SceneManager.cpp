#include "SceneManager.h"

//Clearing the scenes allocated in the heap
SceneManager::~SceneManager()
{
	std::map<std::string, Scene*>::iterator scenesIterator = scenes.begin();
	while (scenesIterator != scenes.end())
	{
		delete (*scenesIterator).second;
		scenesIterator++;
	}
}

void SceneManager::AddScene(Scene* sceneToAdd)
{
	std::string sceneName = sceneToAdd->GetIdentifier();
	this->scenes.emplace(sceneName, sceneToAdd);
	if (this->scenes.size() == 1) StackScene(sceneName);
}

void SceneManager::StackScene(std::string sceneName)
{
	this->stackOfScenes.push(scenes[sceneName]);
}

void SceneManager::PopScene(void)
{
	int popForce = this->stackOfScenes.top()->GetPopForce();
	for (int i = 0; i < popForce; i++)
	{
		this->stackOfScenes.pop();
	}
}

void SceneManager::Update(sf::RenderWindow& window)
{
	if (stackOfScenes.empty())return;
	this->stackOfScenes.top()->Update(window);
}

void SceneManager::RenderScene(sf::RenderWindow& window)
{
	if (stackOfScenes.empty())return;
	this->stackOfScenes.top()->RenderScene(window);
}

void SceneManager::HandleEvent(sf::Event &event, sf::RenderWindow& window)
{
	if (stackOfScenes.empty())return;
	this->stackOfScenes.top()->HandleEvent(event, window);
}
