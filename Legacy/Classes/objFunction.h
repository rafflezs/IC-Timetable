#ifndef _OBJ_FUNCTION
#define _OBJ_FUNCTION

#include "solution.h"

class ObjFunction{
    public:
        int sixthSlot = 0;  //Increases if use of sixth timeslot of a period
        int gapWindow = 0;  //Increases if theres a gap between used time slots
        int gapDays = 0;    //Increases if theres a gap between worked days
        int total = 0;

        int workDays[6];
        int workshift[6][3];

        int objFunctionCalc(Solution* solution); //--> Maybe I should use a function for every atribute
        int objSixthSlot(Schedule* grade);
        int objGapWindow(Schedule* teacher);
        int objGapDays(Schedule* teacher);
};

#endif // !_OBJ_FUNCTION