#pragma once

#include <SFML/Graphics.hpp>

#include "IGraphicsManager.h"
#include "SpriteSheet.h"
#include "SpriteSheetFactory.h"
#include "IDrawable.h"
#include "IDrawer.h"

class GraphicsManagerSFML :
public IGraphicsManager
{
 public:
  ~GraphicsManagerSFML(void);
  GraphicsManagerSFML(void);
  virtual void reset();
  virtual void clear();
  virtual void draw(const Drawable*, const ValueDrawer&) override;
  virtual void display();
  

  template<typename T>
    static const sf::Rect<T> rectangleToSFMLRect(const Rectangle<T>&);

  const sf::Window& getWindow() const;
  const sf::Texture* getTextureFromFilename(const std::string& filename);
 private:
  sf::RenderWindow window;
  sf::View view;

  std::map<std::string, sf::Texture*> textures;
};
