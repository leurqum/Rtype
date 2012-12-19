#pragma once

#include <SFML/Graphics.hpp>

#include "IGraphicsManager.h"

class GraphicsManagerSFML :
	public IGraphicsManager
{
public:
	~GraphicsManagerSFML(void);

	virtual void reset();
	virtual void addDrawableToScene(const IDrawable& drawable);
	virtual void draw();
	virtual IDrawable* createDrawableFrom( /* this would take a protocol drawable as parameter */ );
	virtual void deleteDrawable(const IDrawable*);

	static GraphicsManagerSFML* getInstance();
	template<typename T>
	static const sf::Rect<T>& rectangleToSFMLRect(const Rectangle<T>&);

	const sf::Window& getWindow() const;
private:
	GraphicsManagerSFML(void);

	static GraphicsManagerSFML* _instance;
	sf::RenderWindow window;
};

