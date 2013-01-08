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
  void setInterpolation(int); // INFO: 0 means instant change between rectangle of animations. (default is 0)
  void setSmoothFrames(bool);
  void setTimeBetweenAnimationFrame(float milliseconds);
  void setSmoothLoop(bool smloop); // INFO: this will determine if we interpolate between last and first frame of animation. (default = true)
  class Iterator
  {
  public:
    Iterator(const SpriteSheet& s);
    // NOTE: we don't return a reference because the rectangle might be constructed in the function (in case of interpolation)
    Rectangle<int> getValue() const; // TODO: operator* would be more iterator-like

    // FIXME: we might want to increase(float elapsedMilliseconds) so the SpriteSheet manages entirely all its flow.
    void increase(float miliseconds); // TODO: operator++ would be more iterator-like

	// NOTE: these 2 are pretty special, it's like manually handled animation
	// TODO: implement these
	// void increase_index(int nb_index = 1);
	// void increase_animation(float nb_anim = 1);
    void increase_iterator();

	void setAnimation(int animationId); // operator=(int) ? not sure...
  private:
    const SpriteSheet& ss;
    int animationId;
    Rectangle<int> const * current;
    std::list< Rectangle<int> >::const_iterator* nextRect;
	int index_interpolation;
	float elapsedTime;
  };

  // private: // FIXME: this should be private/protected, but Iterator should be friend with it.
  int nb_interp;
  bool smoothFrames;
  float time_between_frames;
  bool smoothLoop;
  std::string filename;
  std::map<int, std::list<Rectangle<int> > > animations;

};
