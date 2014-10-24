//
//  ObjectsFastFactory.h
//  KillyCraft
//
//  Created by Ricard Pérez del Campo on 21/10/14.
//
//

#ifndef __KillyCraft__ObjectsFastFactory__
#define __KillyCraft__ObjectsFastFactory__

namespace MelonGames
{
	namespace KillyCraft
	{
		class MapObject;
		
		namespace ObjectsFastFactory
		{
			MapObject* createPlayerObject();
			MapObject* createEnemyObject();
		}
	}
}

#endif /* defined(__KillyCraft__ObjectsFastFactory__) */
