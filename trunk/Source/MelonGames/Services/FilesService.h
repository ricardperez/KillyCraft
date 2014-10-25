//
//  FilesService.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 25/10/14.
//  Copyright (c) 2014 MelonGames. All rights reserved.
//

#ifndef __KillyCraft__FilesService__
#define __KillyCraft__FilesService__

#include "Service.h"
#include <vector>
#include <string>

namespace MelonGames
{
	class FilesService : public Service
	{
	public:
		DECLARE_TYPE_WITH_BASE_TYPE(FilesService, Service);
		
		void addDirectory(const std::string& directory);
		std::string getPathForFile(const std::string& fileName) const;
		
	private:
		std::vector<std::string> directories;
	};
}

#endif /* defined(__KillyCraft__FilesService__) */
