#pragma once

#include <SFML/Graphics.hpp>

#include "IGraphicsManager.h"
#include "Drawable.h"
#include "SpriteSheet.h"
#include "SpriteSheetFactory.h"


class Drawable;

class GraphicsManagerSFML :
public IGraphicsManager
{
 public:
  ~GraphicsManagerSFML(void);
  GraphicsManagerSFML(void);
  virtual void reset();
  virtual void clear();
  virtual void draw(IDrawable*);
  virtual void display();
  virtual void update(float);
  virtual IDrawable* updateDrawableFrom(IDrawable* old, const Protocol::drawable& d );
  virtual void deleteDrawable(const IDrawable*);
  

  template<typename T>
    static const sf::Rect<T> rectangleToSFMLRect(const Rectangle<T>&);

  const sf::Window& getWindow() const;
  const sf::Texture* getTextureFromFilename(const std::string& filename);
 private:
  sf::RenderWindow window;
  sf::View view;
  std::list<Drawable*> drawables; // list of created drawables

  std::map<std::string, sf::Texture*> textures;
};

