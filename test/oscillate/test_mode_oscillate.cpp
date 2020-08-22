#include <unity.h>
//#include "../src/modes.h"
#include "modes.h"

#ifdef UNIT_TEST

void test_setOscillate_sets_timer()
{
    setOscillate(true);
    TEST_ASSERT_TRUE(oscillateOn());
}

void test_setOsciallate_turns_fan_on_if_off()
{
    setOscillate(true);
    TEST_ASSERT_TRUE(powerOn());
}

void test_setOscillate_doesnt_turn_fan_off_if_on()
{
    setOscillate(true);
    setOscillate(false);
    TEST_ASSERT_TRUE(powerOn());
}
int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_setOscillate_sets_timer);

    UNITY_END();

    return 0;
}

#endif