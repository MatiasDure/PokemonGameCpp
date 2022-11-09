#include "GameObject.h"

GameObject::GameObject(string identifier, GameObject* parent) :
	identifier(identifier),
	parent(parent),
	active(true)
{
	position.x = 0;
	position.y = 0;
}

GameObject::GameObject(const GameObject& other) :
	identifier(other.GetIdentifier()),
	position(other.GetPosition()),
	parent(other.GetParent()) {}

GameObject::~GameObject()
{
	std::cout << "Destroying " << this->GetIdentifier() << endl;
}

void GameObject::AddChild(GameObject* objToAdd)
{
	children.push_back(objToAdd);
	objToAdd->SetParent(this);
}

void GameObject::RemoveChild(GameObject& objToRemove)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (*children[i] == objToRemove)
		{
			children.erase(children.begin() + i);
			objToRemove.RemoveParent();
			break;
		}
	}
}

void GameObject::SetParent(GameObject* parent)
{
	this->parent = parent;
}

void GameObject::RemoveParent()
{
	if (this->parent == NULL) return;
	parent->RemoveChild(*this);
	this->parent = NULL;
}

void GameObject::MoveObj(const sf::Vector2f vec)
{
	MoveObj(vec.x, vec.y);
}

void GameObject::MoveObj(const float x, const float y)
{
	position.x += x;
	position.y += y;
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->MoveObj(x, y);
	}
}

void GameObject::SetPosition(const float x, const float y)
{
	position.x = x;
	position.y = y;
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->MoveObj(x, y);
	}
}

void GameObject::HandleEvent(sf::Event& event, sf::RenderWindow& window) { CheckActive(active) }
void GameObject::RenderGameObject(sf::RenderWindow& window) { CheckActive(active) }
void GameObject::Update(sf::RenderWindow& window) { CheckActive(active) }

bool GameObject::HasParent() const
{
	return this->parent != NULL;
}

GameObject* GameObject::GetParent() const
{
	if (this->HasParent()) return parent;
}

sf::Vector2f GameObject::GetPosition() const
{
	return this->position;
}

void GameObject::SetActive(bool activate)
{
	active = activate;
}

string GameObject::GetIdentifier() const
{
	return this->identifier;
}

bool GameObject::operator==(const GameObject& other) const
{
	return this->identifier == other.GetIdentifier();
}