//
//  ParticleBatch2D.cpp
//  JNgine
//
//  Created by Honzik on 27.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "ParticleBatch2D.hpp"

namespace JN {
    
    ParticleBatch2D::ParticleBatch2D() {
        
    }
    
    ParticleBatch2D::~ParticleBatch2D() {
        delete[] _particles;
    }
    
    
    
    void ParticleBatch2D::init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle&, float)> updateFunc) {
        _maxParticles = maxParticles;
        _particles = new Particle[maxParticles];
        _decayRate = decayRate;
        _updateFunc = updateFunc;
        
        
    }
    
    int ParticleBatch2D::findFreeParticle() {
        for (int i = _lastFreeParticle; i < _maxParticles ; i++) {
            if (_particles[i].life <= 0) {
            _lastFreeParticle = i;
            return i;
            }
        }
        for (int i = 0; i < _lastFreeParticle ; i++) {
            if (_particles[i].life <= 0) {
                _lastFreeParticle = i;
                return i;
            }
        }

        printf("No free particles found!!!");
        _lastFreeParticle = 0;
        return 0;
    }
    
    void ParticleBatch2D::addParticle(glm::vec2& position, glm::vec2 velocity, Color& color, float width) {
        int particleIndex = findFreeParticle();
        auto& p = _particles[particleIndex];
        p.life = 1.0f;
        p.position = position;
        p.velocity = velocity;
        p.color = color;
        p.width = width;
        
    }
    
    void ParticleBatch2D::update(float deltaTime) {
        for (int i = 0; i < _maxParticles; i++) {
            auto& p = _particles[i];
            if (p.life > 0.0f) {
                // particle is active
                _updateFunc(_particles[i], deltaTime);
                p.life -= _decayRate * deltaTime;
            }
        }
        
    }
    
    
    void ParticleBatch2D::draw(SpriteBatch * spriteBatch) {
        for (int i = 0; i < _maxParticles; i++) {
            auto& p = _particles[i];
            if (p.life > 0.0f) {
                // particle is active
                spriteBatch->draw(glm::vec4(p.position, p.width, p.width),
                                 _UV_COORDS , _texture.id, 0.0f, p.color);
        
            }
        }
    }
    
    
    
}
