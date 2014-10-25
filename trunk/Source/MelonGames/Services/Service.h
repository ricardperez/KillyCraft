//
//  Service.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__Service__
#define __KillyCraft__Service__

#include "MelonGames/DeclaredTypes.h"

namespace MelonGames
{
	class Service
	{
	public:
		DECLARE_BASE_TYPE(Service);
		
		virtual ~Service();
	};
}

#endif /* defined(__KillyCraft__Service__) */
