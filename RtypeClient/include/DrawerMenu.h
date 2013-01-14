#pragma once

#include <array>

#include "ADrawer.h"
#include "DrawableGeneric.h"
#include "FactoryDrawable.h"
#include "DrawerUDrawable.h"
#include "IInputManagerSFML.h"
#include "ValueDrawer.h"

#include <vector>

class DrawerMenu : public ADrawer // no inheritance from DrawerLayer because it doesnt upgrade its targets
{
 public:
  DrawerMenu(const std::string&); // TODO: give skins for buttons/arrow ?

  virtual void drawTo(IGraphicsManager*) const override;
  virtual void drawTo(IGraphicsManager*, const ValueDrawer&) const override;

  virtual void update(float ms) override;

  void checkInput(IInputManagerSFML*);

  void addButton(const std::string&);
  int getSelectedId() const; // -1 means no selection

  void resetSelections();

  enum selectionType
  {
    UNSELECTED,
    HOVER,
    SELECTED,
    VALIDATED
  };
  selectionType getSelectionType() const;

 protected:
  void selectionForward();
  void selectionBackward();
  void select();
  void validate();

 private:
  void updateArrowPosition();
  int selectionId;
  selectionType status;

  std::vector<DrawerUDrawable> buttons;
  std::vector<std::string> texts;

  DrawerUDrawable arrow;
};
