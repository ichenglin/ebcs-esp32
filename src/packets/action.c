#include "packets/action.h"

void action_set_category(action_t *action, uint8_t category) {
    action->category = category;
}