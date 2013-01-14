#include "DrawerMenu.h"

DrawerMenu::DrawerMenu(const std::string& firstButton) : arrow(DrawableGeneric(*FactoryDrawable::getInstance()->createSelectionArrow()))
{
  selectionId = 0;
  status = selectionType::HOVER;
  addButton(firstButton);
  std::list<ValueDrawer > arrowAnimation;
  ValueDrawer d;
  
  arrowAnimation.push_back(d);
  d.position.x = 10;
  arrowAnimation.push_back(d);
  d.position.x = 0;
  arrowAnimation.push_back(d);
  arrow.setAnimation((new Animation<ValueDrawer>(arrowAnimation, 500, true)));
  updateArrowPosition();
}

void DrawerMenu::drawTo(IGraphicsManager* gm) const
{
  // FIXME: maybe one loop would be more efficient...
  // not sure though; and we would have to use 2 iterators, so the code would be more complex.

  for (const ADrawer& d : buttons)
    {
      d.drawTo(gm, this->getModifiedValue());
    }
  int i = 0;
  for (const std::string& t : texts)
    {
      gm->write(t, this->getModifiedValue() + ValueDrawer(42,  i * 42)); // FIXME: we don't put t in coherency with the button, so moving a single button would cause problems.
      i++;
    }
  
  arrow.drawTo(gm, this->getModifiedValue());
}

void DrawerMenu::drawTo(IGraphicsManager* gm, const ValueDrawer& modifier) const
{
  for (const DrawerUDrawable& d : buttons)
    d.drawTo(gm, this->getModifiedValue() + modifier);
  arrow.drawTo(gm, this->getModifiedValue() + modifier);
}

void DrawerMenu::update(float ms)
{
  ADrawer::update(ms);
  updateArrowPosition();
  for (DrawerUDrawable& d : buttons)
    d.update(ms);
  arrow.update(ms);
}

void DrawerMenu::checkInput(IInputManagerSFML* im)
{
  const Vector2<bool>& returnKey(im->getKeyStatus(sf::Keyboard::Return));
  if (!returnKey.x && returnKey.y)
    {
      select();
      // buttons[selectionId].animate(1);
      // status = selectionType::SELECTED;
    }
  else if (returnKey.x && !returnKey.y // && status == selectionType::SELECTED
	   )
    {
      validate();
      // status = selectionType::VALIDATED;
    }

  const Vector2<bool>& downKey(im->getKeyStatus(sf::Keyboard::Down));
  if (!downKey.x && downKey.y)
    {
      selectionForward();
      // buttons[selectionId].animate(0);
      // selectionId++;
      // status = selectionType::HOVER;
      // if (selectionId >= buttons.size())
      // 	selectionId = 0;
    }
  const Vector2<bool>& upKey(im->getKeyStatus(sf::Keyboard::Up));
  if (!upKey.x && upKey.y)
    {
      selectionBackward();
      // buttons[selectionId].animate(0);
      // selectionId--;
      // status = selectionType::HOVER;
      // if (selectionId < 0)
      // 	selectionId = buttons.size() - 1;
    }
}

void DrawerMenu::addButton(const std::string& s)
{  
  buttons.push_back(DrawerUDrawable(DrawableGeneric(*FactoryDrawable::getInstance()->createButton())));
  ValueDrawer d;
  d.position = Vector2<float>(30, (buttons.size() - 1) * 42);
  buttons.back().setInitialValue(d);

  // Create the text
  texts.push_back(s);
}

int DrawerMenu::getSelectedId() const
{
  return selectionId;
}

DrawerMenu::selectionType DrawerMenu::getSelectionType() const
{
  return status;
}

void DrawerMenu::updateArrowPosition()
{

  // TODO: check if it's still ok, like, if no buttons have been deleted and stuff.
  // or do this in another function..
  arrow.setInitialValue(ValueDrawer(0, (selectionId) * 42, 0, 0, 0));

}

void DrawerMenu::selectionForward()
{
  buttons[selectionId].animate(0);
  selectionId++;
  status = selectionType::HOVER;
  if (selectionId >= buttons.size())
    selectionId = 0;
}

void DrawerMenu::selectionBackward()
{
  buttons[selectionId].animate(0);
  selectionId--;
  status = selectionType::HOVER;
  if (selectionId < 0)
    selectionId = buttons.size() - 1;
}

void DrawerMenu::select()
{
  if (status == selectionType::HOVER)
    {
      buttons[selectionId].animate(1);
      status = selectionType::SELECTED;
    }
}

void DrawerMenu::validate()
{
  if (status == selectionType::SELECTED)
    {
      status = selectionType::VALIDATED;
    }
}
void DrawerMenu::resetSelections()
{
  status = selectionType::HOVER;
  for (DrawerUDrawable& d : buttons)
    d.animate(0);
  updateArrowPosition();
}
