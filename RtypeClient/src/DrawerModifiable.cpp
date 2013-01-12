// #include "DrawerModifiable.h"

// DrawerModifiable::DrawerModifiable(const Vector2<float>& p)
// {
  
// }

// Vector2<float> DrawerModifiable::getPosition() const
// {
//   return modifiedPosition;
// }

// void DrawerModifiable::setPosition(const Vector2<float>& p)
// {
//   position = p;
// }

// void DrawerModifiable::update(float ms)
// {
//   modifiedPosition.x = position.x;
//   modifiedPosition.y = position.y;
//   std::cout << "position de base: " << modifiedPosition.x << std::endl;
//   for (Animation::Iterator& i : modifiers)
//     {
//       const Rectangle<int>& r(i.getValue());
//       std::cout << "modifier: [" << r.position.x << ";" << r.position.y << "]" << std::endl;
//       modifiedPosition.x += r.position.x;
//       modifiedPosition.y += r.position.y;
//       i.increase(ms);
//       // TODO: implement scaling ? rotation ?
//     }
//   std::cout << "position modifiee: " << modifiedPosition.x << std::endl;
// }

// void DrawerModifiable::addModifier(const Animation& a)
// {
//   modifiers.push_back(Animation::Iterator(a));
// }
