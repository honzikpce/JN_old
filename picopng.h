//
//  picopng.h
//  GameEngine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#ifndef picopng_h
#define picopng_h
#include <vector>


namespace JN {

extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);


}
    
#endif /* picopng_h */
