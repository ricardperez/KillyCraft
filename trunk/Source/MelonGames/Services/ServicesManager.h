//
//  ServicesManager.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__ServicesManager__
#define __KillyCraft__ServicesManager__

#include <vector>
#include "Service.h"

namespace MelonGames
{
	class ServicesManager
	{
	public:
		static ServicesManager& getInstance();
		
		void add(Service* service);
		
		template <typename T>
		T* get() const;
		
	private:
		std::vector<Service*> services;
	};
	
	template <typename T>
	T* ServicesManager::get() const
	{
		for (auto service : services)
		{
			if (service->isA<T>())
			{
				return (T*)service;
			}
		}
		return nullptr;
	}
}

#endif /* defined(__KillyCraft__ServicesManager__) */
