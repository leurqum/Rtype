#pragma once

#include <list>

#include "Rectangle.h"

class Animation
{
public:
  class Iterator
  {
  public:
    Iterator(const Animation& s);

    // NOTE: we don't return a reference because the rectangle might be constructed in the function (in case of interpolation)
    Rectangle<int> getValue() const; // TODO: operator* would be more iterator-like

    // FIXME: we might want to increase(float elapsedMilliseconds) so the SpriteSheet manages entirely all its flow.
    void increase(float miliseconds); // TODO: operator+ would be more iterator-like

    void increase_iterator();

    // this is const, and it's pretty useful to access it, so public.
    const Animation& a;
  private:
    Rectangle<int> const * current;
    std::list< Rectangle<int> >::const_iterator* nextRect;
    int index_interpolation;
    float elapsedTime;
  };

  //  const std::list<Rectangle<int> >& getFrames() const;


  Animation(std::list<Rectangle<int> > fs, float framingTime, bool sml = false, int nb_interpolation = 0, bool smoothF = false);


  // private: // FIXME: this should be private but friend with iterator
  // NOTE: might be public as long as it's constant.
  const std::list<Rectangle<int> > frames;


  const float time_between_frames; // time between the start of a frame and the end of it.
  const bool smoothLoop; // if last frame goes instantly to first frame or interpole and/or smoothLoop.
  // FIXME: delete this smoothLoop, it's useless, it just avoids the creation of a single frame but add significant complexity.
  const int nb_interp; // interpolate the position of the different frames (it creates [nb_interp] new frames between the frames).
  // (kinda useless, if you think a bit, but it makes less lines sometimes for creating an animation, and it's pretty readable.
  const bool smoothFrames; // it's the high level of interpolate, it makes a full fluid interpolation depending on time between the frames (interpolated frames are counted as frames).
};
