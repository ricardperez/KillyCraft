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
#include "Component/ComponentsFactory.h"
#include "MelonGames/JsonUtil.h"

#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"
#include "json/json.h"

namespace MelonGames
{
    namespace KillyCraft
    {
        Json::Value* ObjectTemplate::getComponentJson(const std::string& componentType)
        {
            for (Json::Value& componentJson : json["components"])
            {
                if (componentType == componentJson["type"].asString())
                {
                    return &componentJson;
                }
            }
            
            return nullptr;
        }
        
        MapObjectsFactory::MapObjectsFactory()
        {
        }
        
        void MapObjectsFactory::mergeTemplate(const ObjectTemplate& superTemplate, ObjectTemplate& baseTemplate) const
        {
            for (const auto& superComponentJson : superTemplate.json["components"])
            {
                std::string componentName = superComponentJson["type"].asString();
                
                if (auto baseComponentJsonPtr = baseTemplate.getComponentJson(componentName))
                {
                    JsonUtil::mergeContentToBase(superComponentJson, *baseComponentJsonPtr, JsonUtil::MergeType::eAutomatic);
                }
                else
                {
                    baseTemplate.json["components"].append(superComponentJson);
                }
            }
        }
        
        void MapObjectsFactory::addTemplatesFromFile(const std::string& filename)
        {
            auto& templates = templatesByFile[filename];
            
            Json::Value json;
            std::string contents = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
            Json::Reader reader;
            reader.parse(contents, json);
            
            const Json::Value& objectsJson = json["obj"];
            
            for (const auto objectJson : objectsJson)
            {
                std::string name = objectJson["name"].asString();
                unsigned int nameHash = Crypto::stringHash(name);
                ObjectTemplate t;
                t.name = name;
                t.json = objectJson;
                
                std::string superName = objectJson["super"].asString();
                if (!superName.empty())
                {
                    unsigned int superHash = Crypto::stringHash(superName);
                    auto superIt = templates.find(superHash);
                    assert(superIt != templates.end() && "The super type has to be declared before its children.");
                    if (superIt != templates.end())
                    {
                        mergeTemplate(superIt->second, t);
                    }
                }
                
                t.abstract = objectJson["abstract"].asBool();
                
                templates[nameHash] = t;
            }
        }
        
        MapObject* MapObjectsFactory::createObject(const std::string& name) const
        {
            unsigned int hash = Crypto::stringHash(name);
            for (const auto& templatesIt : templatesByFile)
            {
                const auto& templates = templatesIt.second;
                const auto it = templates.find(hash);
                if (it != templates.end())
                {
                    return createObject(it->second);
                }
            }
            
            return nullptr;
        }
        
        std::vector<std::string> MapObjectsFactory::getObjectsNamesForFile(const std::string& filename) const
        {
            std::vector<std::string> result;
            
            auto it = templatesByFile.find(filename);
            if (it != templatesByFile.end())
            {
                for (auto& componentIt : it->second)
                {
                    const ObjectTemplate& objectTemplate = componentIt.second;
                    if (!objectTemplate.abstract)
                    {
                        result.push_back(objectTemplate.name);
                    }
                }
            }
            
            return result;
        }
        
        MapObject* MapObjectsFactory::createObject(const ObjectTemplate& t) const
        {
            assert(!t.abstract && "Can't instantiate an abstract template");
            
            MapObject* result = new MapObject();
            
            for (const auto& componentJson : t.json["components"])
            {
                Component* component = ComponentsFactory::createComponent(componentJson);
                
                if (component)
                {
                    result->addComponent(component);
                }
            }
            
            return result;
        }
    }
}