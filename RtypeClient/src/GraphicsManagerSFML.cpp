#include "GraphicsManagerSFML.h"


GraphicsManagerSFML::GraphicsManagerSFML(void) : window(sf::VideoMode(800, 600, 32), "what ?")
{
	spriteSheets.push_back(new SpriteSheet());
	spriteSheets.front()->filename = "sprites/r-typesheet42.gif";

	std::map<int, std::list<Rectangle<int> > > animList;
	std::list<Rectangle<int> > firstAnim;
	firstAnim.push_back(Rectangle<int>(30, 15));
	firstAnim.push_back(Rectangle<int>(30, 15, Vector2<int>(30, 0)));
	spriteSheets.front()->animations[0] = firstAnim;
}


GraphicsManagerSFML::~GraphicsManagerSFML(void)
{
}

void GraphicsManagerSFML::reset()
{

}
void GraphicsManagerSFML::addDrawableToScene(const IDrawable& drawable)
{
	window.draw(sf::Sprite(*getTextureFromFilename(drawable.getSpriteSheetFilename()), GraphicsManagerSFML::rectangleToSFMLRect( drawable.getRectSpriteSheet())));
}
void GraphicsManagerSFML::draw()
{
	window.clear(sf::Color());
	for( std::pair<int, Drawable*> dpair : drawables)
	{
		window.draw(sf::Sprite(*getTextureFromFilename(dpair.second->getSpriteSheetFilename()), GraphicsManagerSFML::rectangleToSFMLRect( dpair.second->getRectSpriteSheet())));		
	}
	window.display();
}

IDrawable* GraphicsManagerSFML::createDrawableFrom( const Protocol::drawable& d )
{
	Drawable* ret = new Drawable(*spriteSheets.front());

	drawables[d.id] = ret;
	return ret;
}
void GraphicsManagerSFML::deleteDrawable(const IDrawable*)
{

}

GraphicsManagerSFML* GraphicsManagerSFML::_instance = nullptr;

GraphicsManagerSFML* GraphicsManagerSFML::getInstance()
{
	if (_instance == nullptr)
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

const sf::Texture* GraphicsManagerSFML::getTextureFromFilename(const std::string& filename)
{
	if (textures[filename] == nullptr)
	{
		textures[filename] = new sf::Texture();
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