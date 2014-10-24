//
//  Map.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#ifndef __KillyCraft__Map__
#define __KillyCraft__Map__

#include <vector>

namespace cocos2d
{
	class Node;
}

namespace MelonGames
{
	namespace KillyCraft
	{
		class MapObject;
		class Player;
		
		class Map
		{
		public:
			Map();
			virtual ~Map();
			
			void setNode(cocos2d::Node* node);
			cocos2d::Node* getNode() const;
			
			void initialize();
			
			Player* getPlayer() const;
			
			void addObject(MapObject* o);
			void removeObjectWhenPossible(MapObject* o);
			
			void update(float dt);
			
		private:
			std::vector<MapObject*> objects;
			
			cocos2d::Node* node;
			Player* player;
		};
	}
}

#endif /* defined(__KillyCraft__Map__) */
