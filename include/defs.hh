//
// Created by Eddie Hoyle on 8/05/17.
//

#ifndef STREAKER_DEFS_HH
#define STREAKER_DEFS_HH

#include <vector>

static const char* SEQUENCE = "(?P<name>\\w+)[\\.|_](?P<padding>[@#]+)(?P<extension>\\.\\w+)$";
static const char* SIMPLE = "(?P<name>\\w+)[\\.|_](?P<padding>[\\-|\\+]?[0-9]+)(?P<extension>\\.\\w+)$";

#endif //STREAKER_DEFS_HH_HH
