/*
 * Mr. 4th Dimention - Allen Webster
 *
 * 22.06.2018
 *
 * Dynamic variable system
 *
 */

// TOP

#if !defined(FRED_DYNAMIC_VARIABLES_H)
#define FRED_DYNAMIC_VARIABLES_H

struct Dynamic_Variable_Slot{
    Dynamic_Variable_Slot *next;
    Dynamic_Variable_Slot *prev;
    String name;
    u64 default_value;
    i32 location;
};

struct Dynamic_Variable_Layout{
    Dynamic_Variable_Slot sentinel;
    i32 location_counter;
};

struct Dynamic_Variable_Block{
    u64 *val_array;
    i32 count;
    i32 max;
};

#endif

// BOTTOM
