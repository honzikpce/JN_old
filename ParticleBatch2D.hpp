//
//  ParticleBatch2D.hpp
//  JNgine
//
//  Created by Honzik on 27.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef ParticleBatch2D_hpp
#define ParticleBatch2D_hpp

#include <stdio.h>
#include "glm/glm.hpp"
#include "Vertex.h"
#include "SpriteBatch.hpp"
#include "glTexture.h"
#include <functional>

namespace JN {
    
    class Particle {
    public:
        //friend class ParticleBatch2D;
        glm::vec2 position = glm::vec2(0.0f);
        glm::vec2 velocity = glm::vec2(0.0f);
        Color color;
        float life = 0.0f;
        float width = 1.0f;
    };
    
    inline void defaultUpdateFunc(Particle& p, float deltaTime) {
         p.position += p.velocity * deltaTime;
    }
    
    class ParticleBatch2D {
    public:
        ParticleBatch2D();
        ~ParticleBatch2D();
        
        
        void init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle&, float)> updateFunc = &defaultUpdateFunc);
        void addParticle(glm::vec2& position, glm::vec2 velocity, Color& color, float width);
        
        void update(float deltaTime);
        void draw(SpriteBatch* spriteBatch);
        
        
    private:
        int findFreeParticle();
        std::function<void(Particle&, float)> _updateFunc;
        const glm::vec4 _UV_COORDS = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        float _decayRate = 0.1f;
        Particle * _particles = nullptr;
        int _maxParticles = 0;
        GLTexture _texture;
        int _lastFreeParticle = 0;
    };
}

#endif /* ParticleBatch2D_hpp */
