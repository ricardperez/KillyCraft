//
//  Map.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 16/10/14.
//
//

#ifndef __KillyCraft__Map__
#define __KillyCraft__Map__

#include "math/CCGeometry.h"
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
        class MapView;
        class SpawnObjectsManager;
        class MapObjectsFactory;
        
        struct MapDefinition
        {
            float height;
            cocos2d::Size screenSize;
            float screenScale;
        };
		
		class Map
		{
		public:
			Map(const MapDefinition& mapDefinition);
			virtual ~Map();
            
            const MapDefinition& getDefinition() const;
			
			void setNode(cocos2d::Node* node);
			
			void initialize();
            
            MapView* getView() const;
			
            Player* getPlayer() const;
			
			void addObject(MapObject* o);
			void removeObjectWhenPossible(MapObject* o);
			
			void update(float dt);
            
            float getElapsedTime() const;
            
            MapObjectsFactory* getFactory() const;
            
            const std::vector<MapObject*>& getObjects() const;
			
		private:
            MapDefinition definition;
			
            std::vector<MapObject*> objects;
            std::vector<MapObject*> objectsToRemove;
			
			cocos2d::Node* node;
            MapView* view;
			Player* player;
            SpawnObjectsManager* spawnObjectsManager;
            MapObjectsFactory* factory;
            
            float elapsedTime;
            
            int nextIdentifier;
            
            bool updating;
		};
	}
}

#endif /* defined(__KillyCraft__Map__) */
