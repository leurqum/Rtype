#include "GraphicsManagerSFML.h"


GraphicsManagerSFML::GraphicsManagerSFML(void) : window(sf::VideoMode(800, 600, 32), "what ?")
{

}


GraphicsManagerSFML::~GraphicsManagerSFML(void)
{
}

void GraphicsManagerSFML::reset()
{

}
void GraphicsManagerSFML::addDrawableToScene(const IDrawable& drawable)
{
	sf::Texture t;
	
	t.loadFromFile(drawable.getSpriteSheetFilename(),
		GraphicsManagerSFML::rectangleToSFMLRect( drawable.getRectSpriteSheet())); // FIXME: don't load each time mothafucker
	window.draw(sf::Sprite(t));
}
void GraphicsManagerSFML::draw()
{
	window.clear(sf::Color());
	window.display();
}

IDrawable* GraphicsManagerSFML::createDrawableFrom( /* this would take a protocol drawable as parameter */ )
{

	return NULL;
}
void GraphicsManagerSFML::deleteDrawable(const IDrawable*)
{

}

GraphicsManagerSFML* GraphicsManagerSFML::_instance = NULL;

GraphicsManagerSFML* GraphicsManagerSFML::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new GraphicsManagerSFML();
	}
	return _instance;
}

template<typename T>
const sf::Rect<T> GraphicsManagerSFML::rectangleToSFMLRect(const Rectangle<T>& r)
{
	sf::Rect<T> r_sfml;
	r_sfml.height = r.height;
	r_sfml.width = r.width;
	r_sfml.left = r.position.x;
	r_sfml.left = r.position.y;
	return r_sfml;
}

const sf::Window& GraphicsManagerSFML::getWindow() const
{
	return window;
}