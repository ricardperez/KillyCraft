//
//  MapObjectsFactory.cpp
//  KillyCraft
//
//  Created by Ricard Perez del Campo on 06/11/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#include "MapObjectsFactory.h"
#include "MelonGames/Crypto.h"
#include "MapObject.h"

#include "platform/CCFileUtils.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        namespace ComponentsFactoryFunctions
        {
            void registerFunctions(std::map<std::string, ComponentFactoryFunction>& functions);
        }
        
        MapObjectsFactory::MapObjectsFactory()
        {
            ComponentsFactoryFunctions::registerFunctions(componentFactoryFunctions);
        }
        
        void MapObjectsFactory::addTemplatesFromFile(const std::string& filename)
        {
            std::string contents = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
            rapidjson::Document jsonDoc;
            jsonDoc.Parse<0>(contents.c_str());
            
            const rapidjson::Value& objectsJson = jsonDoc["obj"];
            for (auto it = objectsJson.MemberonBegin(); it != objectsJson.MemberonEnd(); ++it)
            {
                const rapidjson::Value& objectJson = it->value;
                std::string name = objectJson["name"].GetString();
                unsigned int nameHash = Crypto::stringHash(name);
                ObjectTemplate t;
                t.name = name;
                t.json = &objectJson;
                templates[nameHash] = t;
            }
            
            jsonDocs.emplace_back(jsonDoc);
        }
        
        MapObject* MapObjectsFactory::createObject(const std::string& name) const
        {
            unsigned int hash = Crypto::stringHash(name);
            auto it = templates.find(hash);
            if (it != templates.end())
            {
                return createObject(it->second);
            }
            
            return nullptr;
        }
        
        MapObject* MapObjectsFactory::createObject(const ObjectTemplate& t) const
        {
            MapObject* result = new MapObject();
            
            const rapidjson::Value& components = t.getJson()["components"];
            for (auto it = components.MemberonBegin(); it != components.MemberonEnd(); ++it)
            {
                Component* component = nullptr;
                
                const rapidjson::Value& componentJson = it->value;
                std::string type = componentJson["type"].GetString();
                auto functionIt = componentFactoryFunctions.find(type);
                if (functionIt != componentFactoryFunctions.end())
                {
                    component = functionIt->second(componentJson);
                }
                
                if (component)
                {
                    result->addComponent(component);
                }
                else
                {
                    printf("Could not create a component of type %s\n", type.c_str());
                    delete result;
                    return nullptr;
                }
            }
            
            return result;
        }
    }
}