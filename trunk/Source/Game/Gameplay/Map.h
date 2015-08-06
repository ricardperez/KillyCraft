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
#include <functional>

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
        class MapTransitionController;
        class VFXController;
        class MapTime;
        class MapEvents;
        
        enum class SpawnObjectsType;
        
        struct MapDefinition
        {
            cocos2d::Size screenSize;
            float screenScale;
            std::string fileName;
        };
        
        typedef std::function<bool(const MapObject*)> ObjectsFilter;
		
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
            MapObjectsFactory* getFactory() const;
            MapTransitionController* getMapTransitionController() const;
            VFXController* getVFXController() const;
            MapTime* getTime() const;
            SpawnObjectsManager* getSpawnObjectsManager() const;
            MapEvents* getMapEvents() const;
			
			void addObject(MapObject* o);
			void removeObjectWhenPossible(MapObject* o);
			
			void update(float dt);
            
            const std::vector<MapObject*>& getObjects() const;
            std::vector<MapObject*> getObjectsPassingFilter(const ObjectsFilter& filter) const;
            MapObject* getObjectPassingFilter(const ObjectsFilter& filter) const;
            bool isAnyObjectPassingFilter(const ObjectsFilter& filter) const;
            
			
		private:
            MapDefinition definition;
			
            std::vector<MapObject*> objects;
            std::vector<MapObject*> objectsToRemove;
			
			cocos2d::Node* node;
            MapView* view;
			Player* player;
            SpawnObjectsManager* spawnObjectsManager;
            MapObjectsFactory* factory;
            MapTransitionController* mapTransitionController;
            VFXController* vfxController;
            MapTime* time;
            MapEvents* events;
            
            int nextIdentifier;
            
            bool updating;
		};
	}
}

#endif /* defined(__KillyCraft__Map__) */
