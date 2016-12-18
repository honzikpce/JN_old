//
//  ParticleEngine.cpp
//  JNgine
//
//  Created by Honzik on 27.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "ParticleEngine.hpp"
#include "SpriteBatch.hpp"
#include "ParticleBatch2D.hpp"

namespace JN {
    
    ParticleEngine2D::ParticleEngine2D() {
        
    }
    
    ParticleEngine2D::~ParticleEngine2D() {
        for (int i=0; i < _batches.size(); i++)
            delete _batches[i];
    }
    
    
    
    void ParticleEngine2D::addParticleBatch(ParticleBatch2D* particleBatch) {
        _batches.push_back(particleBatch);
        
    }
    
    
    
    void ParticleEngine2D::update(float deltaTime) {
        for (auto& b : _batches) {
            b->update(deltaTime);
        }
    }
    
    void ParticleEngine2D::draw(SpriteBatch * spriteBatch) {
        for (auto& b : _batches) {
            spriteBatch->begin();
            b->draw(spriteBatch);
            
            
            spriteBatch->end();
            spriteBatch->renderBatch();
            
            
            
        }
    }

    
    
}
