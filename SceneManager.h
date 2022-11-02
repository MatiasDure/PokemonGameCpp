#pragma once
#include <stack>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "Scene.h"

class SceneManager
{
private:
	std::stack<Scene*> stackOfScenes;
	std::map<std::string, Scene*> scenes;

public:
	SceneManager() {};
	~SceneManager();
	void AddScene(Scene *sceneToAdd);
	void StackScene(std::string sceneName);
	void PopScene(void);
	void RenderScene(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void HandleEvent(sf::Event& event, sf::RenderWindow& window);
};