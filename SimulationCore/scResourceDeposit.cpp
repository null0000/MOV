

#include <scResourceDeposit.h>


scResourceDeposit::resource_type scResourceDeposit::remainingValue() const {
    return value;
}

scResourceDeposit::gathered_remaining_pair scResourceDeposit::mine(delta_t time) {
    resource_type mined = std::min((resource_type)(time/100.0), value);
    value -= mined;
    return gathered_remaining_pair(mined, value);
}
