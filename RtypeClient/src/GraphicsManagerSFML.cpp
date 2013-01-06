#include "GraphicsManagerSFML.h"

GraphicsManagerSFML::GraphicsManagerSFML(void) : window(sf::VideoMode(800, 600, 32), "what ?")
{
  reset();
}


GraphicsManagerSFML::~GraphicsManagerSFML(void)
{
}

void GraphicsManagerSFML::reset()
{
  // Initialize the view to a rectangle located at (100, 100) and with a size of 400x200
  view.reset(sf::FloatRect(0, 0, 800, 600));
  // Rotate it by 45 degrees
  // view.rotate(45);
  // Apply it
  window.setView(view);
  // TODO: the view has to follow the game
  // BONUS: we could play with the view (shake) if we take dmg :D
}

void GraphicsManagerSFML::clear()
{
  window.clear(sf::Color());
}

void GraphicsManagerSFML::draw(IDrawable* d)
{
  const SpriteSheet* ss = d->getSpriteSheet();
  if (ss == nullptr)
    return ;
  
  sf::Sprite s(*getTextureFromFilename(ss->getFilename()),
	       GraphicsManagerSFML::rectangleToSFMLRect( d->getRectSpriteSheet()));
s.setPosition(d->getPosition().x, d->getPosition().y);
  window.draw(s);
}

void GraphicsManagerSFML::display()
{
  window.display();
}


void GraphicsManagerSFML::update(float milliseconds)
{
  // TODO: set the drawables to a non updated state. -> then we'll have to delete them if they havn't been updated. (do this in drawable->update(miliseconds); )
}

DrawableRemote* GraphicsManagerSFML::updateDrawableFrom(DrawableRemote* old, const Protocol::drawable& d )
{
  if (old != nullptr)
    {
      // NOTE: we assume d.type is the right type for old, if it's a wrong type, then it's messed up earlier. (but this class doesn't care, it's Drawable who will handle (or not) the matter.)
      old->setUpdate(d);
      return old;
    }
  else
    {

      DrawableRemote* ret = new DrawableRemote();
      ret->setUpdate(d);

      drawables.push_back(ret);
      return ret;
    }
  return nullptr; // bah.
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
      // std::cout << "Tying to open: " << filename << std::endl;
      try {
	// std::cout << "Trying..." << std::endl;
	std::cout << textures[filename]->loadFromFile(filename) << std::endl;
	// std::cout << "done..." << std::endl;
      }
      catch(std::exception e)
	{
	  std::cerr << "holy shit couldn't open: " << filename << std::endl;
	}
    }
  return textures[filename];
}
