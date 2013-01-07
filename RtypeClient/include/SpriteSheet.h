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
  void setInterpolation(int nb_interpolations); // INFO: 0 means instant change between rectangle of animations. (default is 0)
  void setSmoothLoop(bool smloop); // INFO: this will determine if we interpolate between last and first frame of animation. (default = true)
  class Iterator
  {
  public:
    Iterator(const SpriteSheet& s);
    // NOTE: we don't return a reference because the rectangle might be constructed in the function (in case of interpolation)
    Rectangle<int> getValue() const; // TODO: operator* would be more iterator-like

    // FIXME: we might want to increase(float elapsedMilliseconds) so the SpriteSheet manages entirely all its flow.
    void increase(); // TODO: operator++ would be more iterator-like
    void setAnimation(int animationId); // operator=(int) ? not sure...
  private:
    void increase_iterator();
    const SpriteSheet& ss;
    int animationId;
    Rectangle<int> const * current;
    std::list< Rectangle<int> >::const_iterator* nextRect;
    int index_interpolation;
  };

  // private: // FIXME: this should be private/protected, but Iterator should be friend with it.
  int nb_interp;
  bool smoothLoop;
  std::string filename;
  std::map<int, std::list<Rectangle<int> > > animations;

};
