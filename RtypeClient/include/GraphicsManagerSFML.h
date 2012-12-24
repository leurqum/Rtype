#pragma once

#include <SFML/Graphics.hpp>

#include "IGraphicsManager.h"
#include "Drawable.h"
#include "SpriteSheet.h"

class GraphicsManagerSFML :
	public IGraphicsManager
{
public:
	~GraphicsManagerSFML(void);

	virtual void reset();
	virtual void addDrawableToScene(const IDrawable& drawable);
	virtual void draw();
	virtual void update(float);
	virtual IDrawable* createDrawableFrom( const Protocol::drawable& d );
	virtual void deleteDrawable(const IDrawable*);

	static GraphicsManagerSFML* getInstance();
	template<typename T>
	static const sf::Rect<T> rectangleToSFMLRect(const Rectangle<T>&);

	const sf::Window& getWindow() const;
	const sf::Texture* getTextureFromFilename(const std::string& filename);
private:
	GraphicsManagerSFML(void);

	static GraphicsManagerSFML* _instance;
	sf::RenderWindow window;
	std::map<int, Drawable*> drawables; // list of known drawables <id, drawable> : they do not individually know their id.
									   // This class creates and deletes these (factory)
	std::map<std::string, sf::Texture*> textures;
	std::list<SpriteSheet*> spriteSheets;


};

