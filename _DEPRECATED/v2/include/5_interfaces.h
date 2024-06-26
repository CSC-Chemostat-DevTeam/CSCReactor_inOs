#ifndef INTERFACES_H
#define INTERFACES_H

// -------------------------------------------------------
// BOTTOM INTERFACE
void onBottomPressedI();

// -------------------------------------------------------
// BLOKING INTERFACE
void beforeBlockI();

void afterBlockI();

// ----------------------------------------------------
// CMD INTERFACE

void execCmdI();

// ----------------------------------------------------
// PROGRAMMER INTERFACE

void onProgramUpdateI();

// ----------------------------------------------------
// LOGGER INTERFACE
void onLogWriteI();

// ----------------------------------------------------
// STOP INTERFACE
void onStopI();


#endif // INTERFACES_H
