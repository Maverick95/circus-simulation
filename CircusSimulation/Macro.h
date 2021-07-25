#ifndef MACRO_H
#define MACRO_H

#include <wx\event.h>

#define wxBEGIN_EVENT_TABLE_INHERITED_TEMPLATE1(theClass, baseClass, T1) \
    template<class T1> \
    const wxEventTable theClass<T1>::sm_eventTable = \
        { &baseClass<T1>::sm_eventTable, &theClass<T1>::sm_eventTableEntries[0] }; \
    template<class T1> \
    const wxEventTable *theClass<T1>::GetEventTable() const \
        { return &theClass<T1>::sm_eventTable; } \
    template<class T1> \
    wxEventHashTable theClass<T1>::sm_eventHashTable(theClass<T1>::sm_eventTable); \
    template<class T1> \
    wxEventHashTable &theClass<T1>::GetEventHashTable() const \
        { return theClass<T1>::sm_eventHashTable; } \
    template<class T1> \
    const wxEventTableEntry theClass<T1>::sm_eventTableEntries[] = { \

#endif
