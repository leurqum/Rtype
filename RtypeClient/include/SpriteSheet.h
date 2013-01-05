#pragma once

#include <list>
#include <map>
#include <string>

#include "Rectangle.h"

class SpriteSheet
{
 public:
  SpriteSheet(void);
  ~SpriteSheet(void);

  void setFilename(const std::string&);
  const std::string& getFilename() const;
  
  void setAnimations(const std::map<int, std::list<Rectangle<int> > >&);  
  const std::map<int, std::list<Rectangle<int> > >& getAnimations() const;
 private:
  std::string filename;
  std::map<int, std::list<Rectangle<int> > > animations;

};
