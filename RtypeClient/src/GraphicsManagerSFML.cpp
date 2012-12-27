#include "GraphicsManagerSFML.h"


GraphicsManagerSFML::GraphicsManagerSFML(void) : window(sf::VideoMode(800, 600, 32), "what ?")
{
	// TODO: do more SpriteSheets
	spriteSheets.push_back(new SpriteSheet());
	spriteSheets.front()->filename = "sprites/r-typesheet42.gif";

	std::map<int, std::list<Rectangle<int> > > animList;
	std::list<Rectangle<int> > firstAnim;
	firstAnim.push_back(Rectangle<int>(33, 17));
	firstAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(33, 0)));
	firstAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(66, 0)));
	firstAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(99, 0)));
	firstAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(132, 0)));
	firstAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(99, 0)));
	firstAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(66, 0)));
	firstAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(33, 0)));
	spriteSheets.front()->animations[0] = firstAnim;
}


GraphicsManagerSFML::~GraphicsManagerSFML(void)
{
}

void GraphicsManagerSFML::reset()
{

}

void GraphicsManagerSFML::draw()
{
	// FIXME: put that in a scene.
	window.clear(sf::Color());
	for( std::pair<int, Drawable*> dpair : drawables)
	{
		sf::Sprite s(*getTextureFromFilename(dpair.second->getSpriteSheetFilename()),
			GraphicsManagerSFML::rectangleToSFMLRect( dpair.second->getRectSpriteSheet()));
		s.setPosition(dpair.second->getPosition().x, dpair.second->getPosition().y);
		window.draw(s);
	}
	window.display();
}

void GraphicsManagerSFML::update(float milliseconds)
{
	for( std::pair<int, Drawable*> dpair : drawables)
	{
		// FIXME: just update the fkin scenes
		dpair.second->update(milliseconds);
	}
}

IDrawable* GraphicsManagerSFML::createDrawableFrom( const Protocol::drawable& d )
{
	// TODO: use adapted spritesheet depending on type
	Drawable* ret = new Drawable(*spriteSheets.front());

	std::cout << d.xPosition << std::endl;
	ret->setPosition(d.xPosition, d.yPosition);
	drawables[d.id] = ret;
	return ret;
}
void GraphicsManagerSFML::deleteDrawable(const IDrawable*)
{

}

template<typename T>
const sf::Rect<T> GraphicsManagerSFML::rectangleToSFMLRect(const Rectangle<T>& r)
{
	sf::Rect<T> r_sfml;
	r_sfml.height = r.height;
	r_sfml.width = r.width;
	r_sfml.left = r.position.x;
	r_sfml.top = r.position.y;
	return r_sfml;
}

const sf::Window& GraphicsManagerSFML::getWindow() const
{
	return window;
}

const sf::Texture* GraphicsManagerSFML::getTextureFromFilename(const std::string& filename)
{
	if (textures[filename] == nullptr)
	{
		textures[filename] = new sf::Texture();
		// FIXME: use some log like feature.
		std::cout << "Tying to open: " << filename << std::endl;
		try {
			std::cout << "Trying..." << std::endl;
			std::cout << textures[filename]->loadFromFile(filename) << std::endl;
			std::cout << "done..." << std::endl;
		}
		catch(std::exception e)
		{
			std::cout << "holy shit couldn't open: " << filename << std::endl;
		}
	}
	return textures[filename];
}
