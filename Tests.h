#pragma once

#include "activity.h"
#include "ActivitiesRepository.h"
#include "ActivitiesService.h"
#include "Exceptions.h"
#include <assert.h>

class Tests {
private:
    void testDomain();

    void testRepository();

    void testService();

public:
    void testAll();
};
