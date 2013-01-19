#include "SceneHoverMenu.h"

SceneHoverMenu::SceneHoverMenu(IScene& decoratedScene) :
  ASceneHover(decoratedScene), menu("Play")
{
  menu.addButton("Game List"); // list of games
  menu.addButton("Exit ?"); // confirm exit
  menu.setInitialValue(ValueDrawer(200, 160,0, 0, 0));
  isBackground = BgState::FOREGROUND;
}


SceneHoverMenu::~SceneHoverMenu(void)
{
}

IScene* SceneHoverMenu::update(float elapsedTime)
{
  ASceneHover::update(elapsedTime);

  if (isBackground == BgState::FOREGROUND)
    {
      menu.checkInput(SceneManager::getInstance()->getInputManager());
      if (menu.getSelectedId() == 0 && menu.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
	  {
	  try {
	    Network*	network = new Network(std::string("10.18.206.115"), 4242, 4245);
	    return new SceneGame(*this, network);
	  } catch( std::exception e)
	    {
	      std::cout << "failed initializing selected game, maybe you need to be connected" << std::endl;
	      menu.resetSelections();
	    }
	  }
      if (menu.getSelectedId() == 1 && menu.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
	{
	  try {
	    Network*	network = new Network(std::string("10.18.206.115"), 4242, 4245);
	    return new SceneListGame(*this, network);
	  } catch( std::exception e)
	    {
	      std::cout << "failed initializing list of games, maybe you need to be connected" << std::endl;
	      menu.resetSelections();
	    }
	}
      if (menu.getSelectedId() == 2 && menu.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
	{
	  return new SceneHoverConfirmLeave(*this, false);
	}
    }
  if (isBackground == BgState::TO_FOREGROUND)
    {
      menu.resetSelections();
      menu.checkInput(SceneManager::getInstance()->getInputManager());
      isBackground = BgState::FOREGROUND;
    }
  else if (isBackground == BgState::TO_BACKGROUND)
    {
      isBackground = BgState::BACKGROUND;
    }
  menu.update(elapsedTime);
  return this;
}

void SceneHoverMenu::draw()
{
  ASceneHover::draw();
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  menu.drawTo(gm);
}

void SceneHoverMenu::load()
{

}

void SceneHoverMenu::unload()
{

}

void SceneHoverMenu::setToBackground()
{
  isBackground = BgState::BACKGROUND;
  // ValueDrawer d = menu.getInitialValue();

  std::list<ValueDrawer > toBgAnimation;
  toBgAnimation.push_back(ValueDrawer());
  toBgAnimation.push_back(ValueDrawer(-200, -50, -0.3, -0.3)); // TODO: scaling :D

  menu.setAnimation((new Animation<ValueDrawer>(toBgAnimation, 500, true)), 480); // 17 is the average timespan (so 500 - 17 + arbitraryvalue = 480)
  // FIXME: when you background/foreground rapidly, the animation has not ended and we do not track where it was so we're not anymore at the previous place.
  // a way to fix would be to know where is the background, where is the foreground, and to make an animation between these two places, easy.
}

void SceneHoverMenu::setToForeground()
{
  isBackground = BgState::TO_FOREGROUND;
  // ValueDrawer d = menu.getInitialValue();

  std::list<ValueDrawer > toFgAnimation;
  toFgAnimation.push_back(ValueDrawer());
  toFgAnimation.push_back(ValueDrawer(200, 50, 0.3, 0.3)); // TODO: scaling :D

  menu.setAnimation((new Animation<ValueDrawer>(toFgAnimation, 500, true)), 480); // 17 is the average timespan (so 500 - 17 + arbitraryvalue = 480)
  
}
