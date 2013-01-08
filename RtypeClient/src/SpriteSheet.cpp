#include "SpriteSheet.h"


SpriteSheet::SpriteSheet(void)
{
  // nb_interp = 0;
  // time_between_frames = 250; // by default: 4 images per second.
  // smoothLoop = true;
  // smoothFrames = false;
}

SpriteSheet::~SpriteSheet(void)
{
}


void SpriteSheet::setFilename(const std::string& f)
{
  filename = f;
}

const std::string& SpriteSheet::getFilename() const
{
  return filename;
}

void SpriteSheet::setAnimations(const std::map<int, Animation* >& a)
{
  animations = a;
}

const std::map<int, Animation* >& SpriteSheet::getAnimations() const
{
  return animations;
}

// void SpriteSheet::setInterpolation(int nb)
// {
//   nb_interp = nb + 1;
// }

// void SpriteSheet::setSmoothFrames(bool b)
// {
// 	smoothFrames = b;
// }

// void SpriteSheet::setTimeBetweenAnimationFrame(float milliseconds)
// {
// 	time_between_frames = milliseconds;
// }

// void SpriteSheet::setSmoothLoop(bool smloop)
// {
// 	smoothLoop = smloop;
// }

// SpriteSheet::Iterator::Iterator(const SpriteSheet& s) : ss(s), current(nullptr), nextRect(nullptr)
// {
// 	elapsedTime = 0;
// 	animationId = -1;
// }

// #include <iostream>

// Rectangle<int> SpriteSheet::Iterator::getValue() const
// {
//   Rectangle<int> ret = *current;
// 	  // INNER NOTE: revenir au truc d'avant, mais rajouter ce qui suit (github)
//   if (ss.nb_interp != 0 && (*nextRect) != ss.getAnimations().at(animationId).end())
//     {
//       std::cout << (*nextRect)->position.x << std::endl;

//       ret.position.x += ((*nextRect)->position.x - ret.position.x) / (float)ss.nb_interp * index_interpolation;
//       ret.position.y += ((*nextRect)->position.y - ret.position.y) / (float)ss.nb_interp * index_interpolation;
//     }
//   if (ss.smoothFrames)
//     {
// 	  ret.position.x += ((*nextRect)->position.x - ret.position.x) * (elapsedTime / ss.time_between_frames);
// 	  ret.position.y += ((*nextRect)->position.y - ret.position.y) * (elapsedTime / ss.time_between_frames);
//   }



//   //int xIncr;
//   //int yIncr;
//   //if (ss.nb_interp != 0)
//   //  {
// 		//xIncr = ((*nextRect)->position.x - ret.position.x) / (float)ss.nb_interp * index_interpolation;
//   //    yIncr = ((*nextRect)->position.y - ret.position.y) / (float)ss.nb_interp * index_interpolation;
// 		//
// 		////ret.position.x += ((*nextRect)->position.x - ret.position.x) / (float)ss.nb_interp * index_interpolation;
//   ////    ret.position.y += ((*nextRect)->position.y - ret.position.y) / (float)ss.nb_interp * index_interpolation;
//   //  }
//   //if (ss.smoothFrames)
//   //  {
// 	 // xIncr *= (elapsedTime / ss.time_between_frames);
// 	 // yIncr *= (elapsedTime / ss.time_between_frames);
// 	 // }
//   //ret.position.x += xIncr;
//   //ret.position.y += yIncr;
//   return ret;
// }

// void	SpriteSheet::Iterator::increase(float time)
// {
//   elapsedTime += time;
//   while (elapsedTime > ss.time_between_frames)
//     {
// 		std::cout << "spriteupdate: " << elapsedTime << std::endl;
// 	  index_interpolation++;
// 	  if (index_interpolation >= ss.nb_interp)
// 		  increase_iterator();
	  
// 	  elapsedTime -= ss.time_between_frames;

//   }
// }

// void SpriteSheet::Iterator::setAnimation(int animId)
// {
//   animationId = animId;

//   index_interpolation = 0;
//   delete nextRect;
//   nextRect = new std::list< Rectangle<int> >::const_iterator(ss.getAnimations().at(animationId).begin());
//   increase_iterator();
// }

// int SpriteSheet::Iterator::getAnimationId() const
// {
// 	return animationId;
// }

// void SpriteSheet::Iterator::increase_iterator()
// {
//   index_interpolation = 0;
//   std::cout << "increase iterator" << std::endl;
//     if (ss.getAnimations().at(animationId).size() == 1)
//     {
//       *nextRect = ss.getAnimations().at(animationId).begin();
//       current = &(*(*nextRect));
//       return ;
//     }
	
// 	if (ss.nb_interp == 1 && !ss.smoothFrames && *nextRect == ss.getAnimations().at(animationId).end())
//   {
//       *nextRect = ss.getAnimations().at(animationId).begin();
//  }

//   current = &(*((*nextRect)++));
//   if (*nextRect == ss.getAnimations().at(animationId).end() && (ss.nb_interp != 1 || ss.smoothFrames))
//     {
//       *nextRect = ss.getAnimations().at(animationId).begin();
// 	  if (!ss.smoothLoop)
// 		  increase_iterator(); // NOTE: this would not be infinite recursive because of the if before.
//     }
// }
