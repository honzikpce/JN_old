//
//  ParticleEngine.hpp
//  JNgine
//
//  Created by Honzik on 27.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef ParticleEngine_hpp
#define ParticleEngine_hpp

#include <stdio.h>
#include <vector>



namespace JN {
    
    class ParticleBatch2D;
    class SpriteBatch;
    
    class ParticleEngine2D {
    public:
        ParticleEngine2D();
        ~ParticleEngine2D();
        
        void addParticleBatch(ParticleBatch2D* particleBatch);
        
        void update(float deltaTime);
        
        void draw(SpriteBatch * spriteBatch);
        
        
    private:
        std::vector<ParticleBatch2D*> _batches;
        
    };
}


#endif /* ParticleEngine_hpp */
