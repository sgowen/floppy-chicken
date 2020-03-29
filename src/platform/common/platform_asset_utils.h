//
//  platform_asset_utils.h
//  floppycock
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef Platform_Asset_Utils_H
#define Platform_Asset_Utils_H

#include "platform_file_utils.h"

FileData get_asset_data(const char* relative_path);

void release_asset_data(const FileData* file_data);

#endif /* Platform_Asset_Utils_H */