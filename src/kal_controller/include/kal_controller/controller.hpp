#pragma once

#include "types.hpp"

namespace kal_controller {

class Controller {
public:
    ControlCommand getControlCommand(const Pose& vehiclePose,
                                     const Trajectory& trajectory,
                                     bool returnDebugInfo = false) const;

    void setParameters(const Parameters& parameters) {
        parameters_ = parameters;
        parameterInitialized_ = true;
    }

    void throwIfParametersNotInitialized() const;

private:
    Parameters parameters_;
    bool parameterInitialized_{false};
};

} // namespace kal_controller