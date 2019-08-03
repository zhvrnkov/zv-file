//
//  flagsstruct.h
//  myfile
//
//  Created by Vlad Zhavoronkov on 8/1/19.
//  Copyright © 2019 Vlad Zhavoronkov. All rights reserved.
//

#ifndef flagsstruct_h
#define flagsstruct_h

struct _flag {
    unsigned int _READ : 1;
    unsigned int _WRITE : 2;
    unsigned int _UNBUF : 3;
    unsigned int _EOF : 4;
    unsigned int _ERR : 5;
};

#endif /* flagsstruct_h */
