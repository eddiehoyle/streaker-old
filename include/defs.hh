//
// Created by Eddie Hoyle on 8/05/17.
//

#ifndef STREAKER_DEFS_HH
#define STREAKER_DEFS_HH

#include <vector>

/// # or @ sequence
static const char* SEQUENCE = "(?P<name>\\w+)[\\.|_](?P<frame>[@#]+)(?P<extension>\\.\\w+)$";

/// Numbered frame
static const char* FRAME = "(?P<name>\\w+)[\\.|_](?P<frame>[\\-|\\+]?[0-9]+)(?P<extension>\\.\\w+)$";

#endif //STREAKER_DEFS_HH_HH
