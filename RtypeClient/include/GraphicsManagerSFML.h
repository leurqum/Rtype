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
  virtual void reset() override;
  virtual void clear() override;
  virtual void draw(const Drawable*, const ValueDrawer&) override;
  virtual void write(const std::string&, const ValueDrawer&) override;
  virtual void display() override;
  

  template<typename T>
    static const sf::Rect<T> rectangleToSFMLRect(const Rectangle<T>&);

  const sf::Window& getWindow() const;
  const sf::Texture* getTextureFromFilename(const std::string& filename);
 private:
  sf::Font& getFont();
  sf::RenderWindow window;
  sf::View view;
  sf::Font* font;

  std::map<std::string, sf::Texture*> textures;
};
