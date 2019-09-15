#include "AssetManager.h"



AssetManager::AssetManager()
{
	
}



AssetManager::~AssetManager()
{
}

void AssetManager::LoadTexture(std::string name, std::string fileName)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName))
	{
		m_Textures[name] = tex;
		m_Textures[name].setSmooth(true);
		
	}
}

sf::Texture & AssetManager::GetTexture(std::string name)
{
	return m_Textures.at(name);
}

void AssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;
	if (font.loadFromFile(fileName))
		m_Fonts[name] = font;
}

sf::Font & AssetManager::GetFont(std::string name)
{
	return m_Fonts.at(name);
}
