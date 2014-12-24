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
        
		class ObjectsFastFactory
		{
        public:
            static ObjectsFastFactory* getInstance();
			MapObject* createPlayerObject() const;
            MapObject* createProjectile(MapObject* owner) const;
            
        private:
            ObjectsFastFactory() {};
        };
	}
}

#endif /* defined(__KillyCraft__ObjectsFastFactory__) */
