//
//  MapObjectsFactory.h
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__MapObjectsFactory__
#define __KillyCraft__MapObjectsFactory__

#include <string>
#include <map>
#include <vector>
#include "json/value.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        class MapObject;
        class Component;
        
        typedef std::function<Component*(const Json::Value& json)> ComponentFactoryFunction;
        
        struct ObjectTemplate
        {
            std::string name;
            Json::Value json;
        };
        
        class MapObjectsFactory
        {
        public:
            MapObjectsFactory();
            
            void addTemplatesFromFile(const std::string& filename);
            
            MapObject* createObject(const std::string& name) const;
            
        private:
            
            MapObject* createObject(const ObjectTemplate& t) const;
            
        private:
            std::map<unsigned int, ObjectTemplate> templates;
            
            std::map<std::string, ComponentFactoryFunction> componentFactoryFunctions;
        };
    }
}

#endif /* defined(__KillyCraft__MapObjectsFactory__) */
