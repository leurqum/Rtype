#pragma once

template<typename Frame>
class IAnimation
{
 public:
  
  class IIterator
  {
  public:
    virtual ~IIterator() {}
    virtual const Frame& getFrame() const = 0;
    virtual void increase(float ms) = 0;
  };
  virtual IIterator* getIterator() const = 0;
};
