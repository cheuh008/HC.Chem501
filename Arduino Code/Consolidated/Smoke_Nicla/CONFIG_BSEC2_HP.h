#define CONFIG_BSEC2_USE_DEAULT_HP 1

#if CONFIG_BSEC2_USE_DEAULT_HP
// Default Heater temperature and time base(Recommendation)
const uint16_t BSEC2HP_TEMP[] = { 320, 100, 100, 100, 200, 200, 200, 320, 320, 320 };  // HP-354 /
const uint16_t BSEC2HP_DUR[] = { 5, 2, 10, 30, 5, 5, 5, 5, 5, 5 };                     // the duration in steps of 140ms, 5 means 700ms, 2 means 280ms
#else
// customized Heater temperature and time base
const uint16_t BSEC2HP_TEMP[] = { 100, 320, 320, 200, 200, 200, 320, 320, 320, 320 };  // HP-321 /
const uint16_t BSEC2HP_DUR[] = { 43, 2, 2, 2, 21, 21, 2, 14, 14, 14 };                 // the duration in steps of 140ms, 5 means 700ms, 2 means 280ms
#endif